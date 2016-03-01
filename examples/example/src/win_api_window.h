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
	static std::map<HWND, WinApiWindow*> instances_;
	HDC hdc_;
	HWND hwnd_;
	HGLRC hrc_;
	HINSTANCE hinstance_;
	std::function<void()> render_function_;
	std::function<void(long, long)> resize_callback_;
 	std::function<void(long, long)> mouse_move_callback_;
	std::function<void(long)> mouse_click_callback_;
	std::function<void(long, bool)> button_callback_;
	bool is_minimized_;
	long window_width_, window_height_;
	POINT window_position_;
	long window_style_ = WS_OVERLAPPEDWINDOW;
	long window_ex_style_ = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	std::string window_title_;
	bool initialization_seuccess_;

	bool registerWindowClass();
	void unregisterWindowClass();
	bool createWinApiWindow();
	bool initOpenGL();

	void resizeCallback(long width, long height);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
