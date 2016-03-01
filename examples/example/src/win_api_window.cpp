#include "win_api_window.h"


WinApiWindow::WinApiWindow(std::string window_title, long window_width, long window_height, POINT window_position /* = { CW_USEDEFAULT, 0L }*/ )
	: WinApiWindow()
{
	createWindow(window_title, window_width, window_height, window_position);
}


WinApiWindow::WinApiWindow()
{
	render_function_ = []() -> void {};
	resize_callback_ = [](long, long) -> void {};
	mouse_move_callback_ = [](long, long) -> void {};
	mouse_click_callback_ = [](long) -> void {};
	button_callback_ = [](long, bool) -> void {};
}

WinApiWindow::~WinApiWindow()
{
	wglMakeCurrent(hdc_, nullptr);
	wglDeleteContext(hrc_);
	ReleaseDC(hwnd_, hdc_);
	unregisterWindowClass();
}

void WinApiWindow::createWindow(std::string window_title, long window_width, long window_height, POINT window_position /* = { CW_USEDEFAULT, 0L }*/ )
{
	hinstance_ = GetModuleHandle(nullptr);
	window_title_ = window_title;
	window_width_ = window_width;
	window_height_ = window_height;
	window_position_ = window_position;

	initialization_seuccess_ = true;
	if (!(initialization_seuccess_ &= registerWindowClass())) return;
	if (!(initialization_seuccess_ &= createWinApiWindow())) return;
	initialization_seuccess_ &= initOpenGL();
}


bool WinApiWindow::setCoreOpenGL()
{
	if (!wglewIsSupported("WGL_ARB_create_context"))
	{
		MessageBox(nullptr, "OpenGL 3.2+ context not available, update your graphics drivers", "Error", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	const int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		NULL
	};
	wglMakeCurrent(hdc_, nullptr);
	wglDeleteContext(hrc_); // delete OpenGL 2.1 context
	hrc_ = wglCreateContextAttribsARB(hdc_, nullptr, attributes);
	wglMakeCurrent(hdc_, hrc_);
	return true;
}

bool WinApiWindow::isOk()
{
	return initialization_seuccess_;
}

void WinApiWindow::setRenderFunction(std::function<void()> function)
{
	render_function_ = function;
}


void WinApiWindow::setResizeCallback(std::function<void(long, long)> function)
{
	resize_callback_ = function;
}

void WinApiWindow::setMouseMoveCallback(std::function<void(long, long)> function)
{
	mouse_move_callback_ = function;
}

void WinApiWindow::setMouseClickCallback(std::function<void(long)> function)
{
	mouse_click_callback_ = function;
}

void WinApiWindow::setButtonCallback(std::function<void(long, bool)> function)
{
	button_callback_ = function;
}

int WinApiWindow::loop()
{
	MSG msg;
	do
	{
		if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!is_minimized_)
				render_function_();
			SwapBuffers(hdc_);
		}
	} while (msg.message != WM_QUIT);
	return static_cast<int>(msg.wParam);
}

void WinApiWindow::showCursor()
{
	ShowCursor(TRUE);
}

void WinApiWindow::hideCursor()
{
	ShowCursor(FALSE);
}

void WinApiWindow::setCursorPosition(long x, long y)
{
	POINT p = { x, y };
	ClientToScreen(hwnd_, &p);
	SetCursorPos(p.x, p.y);
}

POINT WinApiWindow::getCursorPosition()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd_, &p);
	return p;
}


std::map<HWND, WinApiWindow*> WinApiWindow::instances_;

bool WinApiWindow::registerWindowClass()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.hInstance = hinstance_;
	wcex.lpfnWndProc = WndProc;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszClassName = window_title_.c_str();
	wcex.lpszMenuName = nullptr;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(nullptr, "An error occurred while registering windows class", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void WinApiWindow::unregisterWindowClass()
{
	UnregisterClass(window_title_.c_str(), hinstance_);
}

bool WinApiWindow::createWinApiWindow()
{
	RECT rect = { 0, 0, window_width_, window_height_ };
	AdjustWindowRectEx(&rect, window_style_, FALSE, window_ex_style_);
	unsigned adjusted_width = rect.right - rect.left;
	unsigned adjusted_height = rect.bottom - rect.top;

	hwnd_ = CreateWindowEx(window_ex_style_, window_title_.c_str(), window_title_.c_str(), window_style_,
		window_position_.x, window_position_.y, adjusted_width, adjusted_height, nullptr, nullptr, hinstance_, nullptr);
	instances_[hwnd_] = this;
	if (!hwnd_)
	{
		MessageBox(nullptr, "An error occurred while creating window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ShowWindow(hwnd_, SW_SHOW);
	return true;
}

bool WinApiWindow::initOpenGL()
{
	hdc_ = GetDC(hwnd_);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int format = ChoosePixelFormat(hdc_, &pfd);

	if (!SetPixelFormat(hdc_, format, &pfd))
	{
		MessageBox(nullptr, "An error occurred while setting pixel format to device context", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	hrc_ = wglCreateContext(hdc_);  // creating an OpenGL 2.1 rendering context
	if (!wglMakeCurrent(hdc_, hrc_))
	{
		MessageBox(nullptr, "An error occurred while creating and activating render context", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		MessageBox(nullptr, "An error occurred while initializing glew", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}


void WinApiWindow::resizeCallback(long width, long height)
{
	window_width_ = width;
	window_height_ = height;
	resize_callback_(width, height);
}

LRESULT CALLBACK WinApiWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_MINIMIZED:
			instances_[hwnd]->is_minimized_ = true;
			break;
		case SIZE_RESTORED:
			instances_[hwnd]->is_minimized_ = false;
			instances_[hwnd]->resizeCallback(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		break;
	case WM_MOUSEMOVE:
		instances_[hwnd]->mouse_move_callback_(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		instances_[hwnd]->mouse_click_callback_(msg);
		break;
	case WM_KEYDOWN:
		instances_[hwnd]->button_callback_(wParam, true);
		break;
	case WM_KEYUP:
		instances_[hwnd]->button_callback_(wParam, false);
		break;
	case WM_DESTROY:
		instances_.erase(hwnd);
		PostQuitMessage(EXIT_SUCCESS);
		return EXIT_SUCCESS;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
