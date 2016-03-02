#include <sstream>
#include <functional>
#include <map>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/wglew.h>


class WinApiWindow
{
public:
	WinApiWindow();
	WinApiWindow(std::string window_title, long window_width, long window_height, POINT window_position = { CW_USEDEFAULT, 0L });
	~WinApiWindow();

	void createWindow(std::string window_title, long window_width, long window_height, POINT window_position = { CW_USEDEFAULT, 0L });
	bool setCoreOpenGL();
	bool isOk();
	void setRenderFunction(std::function<void()> function);
	void setResizeCallback(std::function<void(long, long)> function);
	void setMouseMoveCallback(std::function<void(long, long)> function);
	void setMouseClickCallback(std::function<void(long)> function);
	void setButtonCallback(std::function<void(long, bool)> function);
	int loop();
	void showCursor();
	void hideCursor();
	void setCursorPosition(long x, long y);
	POINT getCursorPosition();
private:
	static std::map<HWND, WinApiWindow*> s_instances;
	HDC m_hdc;
	HWND m_hwnd;
	HGLRC m_hrc;
	HINSTANCE m_hinstance;
	std::function<void()> m_render_function;
	std::function<void(long, long)> m_resize_callback;
 	std::function<void(long, long)> m_mouse_move_callback;
	std::function<void(long)> m_mouse_click_callback;
	std::function<void(long, bool)> m_button_callback;
	bool m_is_minimized;
	long m_window_width, m_window_height;
	POINT m_window_position;
	long m_window_style = WS_OVERLAPPEDWINDOW;
	long m_window_ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	std::string m_window_title;
	bool m_initialization_seuccess;

	bool registerWindowClass();
	void unregisterWindowClass();
	bool createWinApiWindow();
	bool initOpenGL();

	void resizeCallback(long width, long height);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
