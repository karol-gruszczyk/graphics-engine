#include "win_api_window.h"


void init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void render()
{
	/*
	Render just an example triangle for demonstration
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	glColor3f(1.f, 0.f, 0.f);
	glVertex2f(0.f, 0.5f);

	glColor3f(-0.5f, 1.f, 0.f);
	glVertex2f(-0.5f, -0.5);

	glColor3f(0.f, 0.f, 1.f);
	glVertex2f(0.5f, -0.5f);

	glEnd();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WinApiWindow window(hInstance, "OpenGL test window", 800, 600);
	if (!window.is_ok())
		return EXIT_FAILURE;
	init();
	window.setRenderFunction(render);
	return window.loop();
}
