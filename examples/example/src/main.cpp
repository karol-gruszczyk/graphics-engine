#include "win_api_window.h"
#include <engine/primitives/rectangle.h>


WinApiWindow window;
engine::Rectangle rect;


void init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	rect.initialize(1.f, 1.f);
}

void resize(long width, long height)
{
	glViewport(0, 0, width, height);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	rect.render();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	window.setResizeCallback(resize);
	window.createWindow("OpenGL test window", 800, 600);
	// window.setCoreOpenGL();  // use to dissable all deprecated functionality and use only core OpenGL
	if (!window.isOk())
		return EXIT_FAILURE;
	init();
	window.setRenderFunction(render);
	return window.loop();
}
