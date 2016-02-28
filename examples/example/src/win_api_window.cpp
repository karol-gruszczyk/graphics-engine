#include "win_api_window.h"


WinApiWindow::WinApiWindow(HINSTANCE hinstance, std::string window_title, long window_width, long window_height,
	long window_horizontal_position /*= 0L*/, long window_vertival_position /*= 0L*/)
{
	createWindow(hinstance, window_title, window_width, window_height, window_horizontal_position, window_vertival_position);
}

WinApiWindow::~WinApiWindow()
{
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(render_context_);
	ReleaseDC(hwnd_, hdc_);
	unregisterWindowClass();
}

void WinApiWindow::createWindow(HINSTANCE hinstance, std::string window_title, long window_width, long window_height, long window_horizontal_position /*= 0L*/, long window_vertival_position /*= 0L*/)
{
	hinstance_ = hinstance;
	window_title_ = window_title;
	window_width_ = window_width;
	window_height_ = window_height;
	window_horizontal_position_ = window_horizontal_position;
	window_vertival_position_ = window_vertival_position;

	initialization_seuccess_ = true;
	initialization_seuccess_ &= registerWindowClass();
	if (!initialization_seuccess_) return;
	initialization_seuccess_ &= createWinApiWindow();
	if (!initialization_seuccess_) return;
	initialization_seuccess_ &= initOpenGL();
}

bool WinApiWindow::isOk()
{
	return initialization_seuccess_;
}

void WinApiWindow::setRenderFunction(std::function<void()> function)
{
	render_function_ = function;
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

void WinApiWindow::getCursorPosition(long& x, long& y)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd_, &p);
	x = p.x;
	y = p.y;
}

bool WinApiWindow::registerWindowClass()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = hinstance_;
	wcex.lpfnWndProc = MsgProc;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszClassName = OPENGL_WINDOW_CLASS_NAME;
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
	UnregisterClass(OPENGL_WINDOW_CLASS_NAME, hinstance_);
}

bool WinApiWindow::createWinApiWindow()
{
	RECT rect = { 0, 0, window_width_, window_height_ };
	AdjustWindowRect(&rect, window_style_, FALSE);
	unsigned adjusted_width = rect.right - rect.left;
	unsigned adjusted_height = rect.bottom - rect.top;

	hwnd_ = CreateWindow(OPENGL_WINDOW_CLASS_NAME, window_title_.c_str(), window_style_, window_horizontal_position_, window_vertival_position_, 
		adjusted_width, adjusted_height, nullptr, nullptr, hinstance_, nullptr);
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

	int format = ChoosePixelFormat(hdc_, &pfd);

	if (!SetPixelFormat(hdc_, format, &pfd))
	{
		MessageBox(nullptr, "An error occurred while setting pixel format to device context", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	render_context_ = wglCreateContext(hdc_);
	if (!wglMakeCurrent(hdc_, render_context_))
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

LRESULT CALLBACK WinApiWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return EXIT_SUCCESS;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
