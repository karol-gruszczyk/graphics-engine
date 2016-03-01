#include "win_api_window.h"


WinApiWindow window;


void init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void resize(long width, long height)
{
	glViewport(0, 0, width, height);
}

void render()
{
	/*
	Render just an example triangle for demonstration
	keep in mind, that this is deprecated code and won't work with core OpenGL
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
	window.setResizeCallback(resize);
	window.createWindow("OpenGL test window", 800, 600);
	// window.setCoreOpenGL();  use to dissable all deprecated functionality and use only core OpenGL
	if (!window.isOk())
		return EXIT_FAILURE;
	init();
	window.setRenderFunction(render);
	return window.loop();
}
