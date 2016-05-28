#include "win_api_window.h"
#include <sstream>
#include <windowsx.h>
#include <gl/glew.h>
#include <gl/wglew.h>

std::map<HWND, WinApiWindow*> WinApiWindow::s_instances;


WinApiWindow::WinApiWindow(std::string window_title, long window_width, long window_height, POINT window_position /* = { CW_USEDEFAULT, 0L }*/)
	: WinApiWindow()
{
	createWindow(window_title, window_width, window_height, window_position);
}

WinApiWindow::WinApiWindow()
{
	m_render_function = []() -> void {};
	m_resize_callback = [](long, long) -> void {};
	m_mouse_move_callback = [](long, long) -> void {};
	m_mouse_click_callback = [](long) -> void {};
	m_button_callback = [](long, bool) -> void {};
}

WinApiWindow::~WinApiWindow()
{
	wglMakeCurrent(m_hdc, nullptr);
	wglDeleteContext(m_hrc);
	ReleaseDC(m_hwnd, m_hdc);
	unregisterWindowClass();
}

void WinApiWindow::createWindow(std::string window_title, long window_width, long window_height, POINT window_position /* = { CW_USEDEFAULT, 0L }*/)
{
	m_hinstance = GetModuleHandle(nullptr);
	m_window_title = window_title;
	m_window_width = window_width;
	m_window_height = window_height;
	m_window_position = window_position;

	m_initialization_seuccess = true;
	if (!(m_initialization_seuccess &= registerWindowClass())) return;
	if (!(m_initialization_seuccess &= createWinApiWindow())) return;
	m_initialization_seuccess &= initOpenGL();
	m_last_frame_time = std::chrono::high_resolution_clock::now();
	setFPSCap();
}

bool WinApiWindow::setCoreOpenGL()
{
	if (!wglewIsSupported("WGL_ARB_create_context"))
	{
		MessageBox(nullptr, "OpenGL 3.2+ context not available, update your graphics drivers", "Error", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	GLint major_version, minor_version;
	glGetIntegerv(GL_MAJOR_VERSION, &major_version);
	glGetIntegerv(GL_MINOR_VERSION, &minor_version);
	const int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_version,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_version,
		NULL
	};
	wglMakeCurrent(m_hdc, nullptr);
	wglDeleteContext(m_hrc); // delete OpenGL 2.1 context
	m_hrc = wglCreateContextAttribsARB(m_hdc, nullptr, attributes);
	wglMakeCurrent(m_hdc, m_hrc);
	return true;
}

bool WinApiWindow::isOk()
{
	return m_initialization_seuccess;
}

void WinApiWindow::setRenderFunction(std::function<void()> func)
{
	m_render_function = func;
}

void WinApiWindow::setResizeCallback(std::function<void(long, long)> func)
{
	m_resize_callback = func;
}

void WinApiWindow::setMouseMoveCallback(std::function<void(long, long)> func)
{
	m_mouse_move_callback = func;
}

void WinApiWindow::setMouseClickCallback(std::function<void(long)> func)
{
	m_mouse_click_callback = func;
}

void WinApiWindow::setButtonCallback(std::function<void(long, bool)> func)
{
	m_button_callback = func;
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
			if (!m_is_minimized)
				m_render_function();
			SwapBuffers(m_hdc);

			auto now = std::chrono::high_resolution_clock::now();
			auto frame_duration = (unsigned)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_frame_time).count();
			long sleep = m_max_frame_time_ms - frame_duration;
			if (m_max_frame_time_ms && sleep > 0)
				Sleep(sleep);
			m_fps = 1000 / ((m_max_frame_time_ms && sleep > 0 ? sleep : 0) + frame_duration);
			m_last_frame_time = std::chrono::high_resolution_clock::now();
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
	ClientToScreen(m_hwnd, &p);
	SetCursorPos(p.x, p.y);
}

POINT WinApiWindow::getCursorPosition()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hwnd, &p);
	return p;
}

void WinApiWindow::showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}

void WinApiWindow::hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void WinApiWindow::setTitle(std::string title)
{
	SetWindowText(m_hwnd, title.c_str());
}

void WinApiWindow::setFPSCap(unsigned fps /*= 60*/)
{
	m_max_frame_time_ms = (unsigned)ceil(1000.0 / fps);
}

unsigned WinApiWindow::getFPS()
{
	return m_fps;
}

void WinApiWindow::close(long quit_message /* = EXIT_SUCCESS */)
{
	PostQuitMessage(quit_message);
}

bool WinApiWindow::registerWindowClass()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.hInstance = m_hinstance;
	wcex.lpfnWndProc = WndProc;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszClassName = m_class_name;
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
	UnregisterClass(m_class_name, m_hinstance);
}

bool WinApiWindow::createWinApiWindow()
{
	RECT rect = { 0, 0, m_window_width, m_window_height };
	AdjustWindowRectEx(&rect, m_window_style, FALSE, m_window_ex_style);
	unsigned adjusted_width = rect.right - rect.left;
	unsigned adjusted_height = rect.bottom - rect.top;

	m_hwnd = CreateWindowEx(m_window_ex_style, m_class_name, m_window_title.c_str(), m_window_style,
		m_window_position.x, m_window_position.y, adjusted_width, adjusted_height, nullptr, nullptr, m_hinstance, nullptr);
	s_instances[m_hwnd] = this;
	if (!m_hwnd)
	{
		MessageBox(nullptr, "An error occurred while creating window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ShowWindow(m_hwnd, SW_SHOW);
	return true;
}

bool WinApiWindow::initOpenGL()
{
	m_hdc = GetDC(m_hwnd);

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

	int format = ChoosePixelFormat(m_hdc, &pfd);

	if (!SetPixelFormat(m_hdc, format, &pfd))
	{
		MessageBox(nullptr, "An error occurred while setting pixel format to device context", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	m_hrc = wglCreateContext(m_hdc);  // creating an OpenGL 2.1 rendering context
	if (!wglMakeCurrent(m_hdc, m_hrc))
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
	m_window_width = width;
	m_window_height = height;
	m_resize_callback(width, height);
}

LRESULT CALLBACK WinApiWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_MINIMIZED:
			s_instances[hwnd]->m_is_minimized = true;
			break;
		case SIZE_RESTORED:
			s_instances[hwnd]->m_is_minimized = false;
			s_instances[hwnd]->resizeCallback(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		break;
	case WM_MOUSEMOVE:
		s_instances[hwnd]->m_mouse_move_callback(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		s_instances[hwnd]->m_mouse_click_callback(msg);
		break;
	case WM_KEYDOWN:
		s_instances[hwnd]->m_button_callback(wParam, true);
		break;
	case WM_KEYUP:
		s_instances[hwnd]->m_button_callback(wParam, false);
		break;
	case WM_CREATE:
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		break;
	case WM_DESTROY:
		s_instances.erase(hwnd);
		PostQuitMessage(EXIT_SUCCESS);
		return EXIT_SUCCESS;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
