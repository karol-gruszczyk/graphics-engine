#include <sstream>
#include <functional>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define GLEW_STATIC
#include <gl/glew.h>

#define OPENGL_WINDOW_CLASS_NAME "OPENGL_WINDOW_CLASS_NAME"


class WinApiWindow
{
public:
	WinApiWindow(HINSTANCE hinstance, std::string window_title, long window_width, long window_height,
		long window_horizontal_position = 0L, long window_vertival_position = 0L);
	~WinApiWindow();

	bool is_ok();
	void setRenderFunction(std::function<void()> function);
	int loop();
private:
	HDC hdc_;
	HINSTANCE hinstance_;
	HWND hwnd_;
	HGLRC render_context_;
	std::function<void()> render_function_;
	long window_width_, window_height_, window_horizontal_position_, window_vertival_position_;
	long window_style_ = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	std::string window_title_;
	bool initialization_seuccess_ = true;

	bool registerWindowClass();
	void unregisterWindowClass();
	bool createWindow();
	bool initOpenGL();

	static LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
