#include <functional>
#include <chrono>
#include <map>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


class WinApiWindow
{
public:
	WinApiWindow();
	WinApiWindow(std::string window_title, long window_width, long window_height, POINT window_position = { CW_USEDEFAULT, 0L });
	~WinApiWindow();

	void createWindow(std::string window_title, long window_width, long window_height, POINT window_position = { CW_USEDEFAULT, 0L });
	bool setCoreOpenGL();
	bool isOk();
	void setRenderFunction(std::function<void()> func);
	void setCleanupFunction(std::function<void()> func);
	void setResizeCallback(std::function<void(long, long)> func);
	void setMouseMoveCallback(std::function<void(long, long)> func);
	void setMouseClickCallback(std::function<void(long)> func);
	void setButtonCallback(std::function<void(long, bool)> func);
	int loop();
	void showCursor();
	void hideCursor();
	void setCursorPosition(long x, long y);
	POINT getCursorPosition();
	void showConsole();
	void hideConsole();
	void setTitle(std::string title);
	void setFPSCap(unsigned fps = 60);
	unsigned getFPS();
	void close(long quit_message = EXIT_SUCCESS);
private:
	static std::map<HWND, WinApiWindow*> s_instances;
	HDC m_hdc;
	HWND m_hwnd;
	HGLRC m_hrc;
	HINSTANCE m_hinstance;
	const char* m_class_name = "OPENGL_WINDOW_CLASS";
	std::function<void()> m_render_function;
	std::function<void()> m_cleanup_function;
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
	std::chrono::steady_clock::time_point m_last_frame_time;
	unsigned m_max_frame_time_ms;
	unsigned m_fps;

	bool registerWindowClass();
	void unregisterWindowClass();
	bool createWinApiWindow();
	bool initOpenGL();

	void resizeCallback(long width, long height);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
