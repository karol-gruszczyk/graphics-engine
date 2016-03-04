#include "win_api_window.h"
#include <engine/primitives/rectangle.h>
#include <engine/shaders/fragment_shader.h>
#include <engine/shaders/vertex_shader.h>
#include <engine/shaders/shader_program.h>
#include <iostream>

WinApiWindow window;
engine::Rectangle rect;
engine::ShaderProgram program;
engine::VertexShader vs;
engine::FragmentShader fs;


void init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	rect.initialize(1.f, 1.f);
	try
	{
		vs.loadFromFile("..\\..\\engine\\glsl\\simple_vs.glsl");
		fs.loadFromFile("..\\..\\engine\\glsl\\simple_fs.glsl");
	}
	catch (engine::ShaderCompileException& e)
	{
		window.showConsole();
		std::cout << e.getErrorMessage() << std::endl;
		std::cin.get();
		window.close(EXIT_FAILURE);
	}

	try
	{
		program.create({ &vs, &fs });
	}
	catch (engine::ShaderLinkException& e)
	{
		window.showConsole();
		std::cout << e.getErrorMessage() << std::endl;
		std::cin.get();
		window.close(EXIT_FAILURE);
	}
	program.bind();
}

void resize(long width, long height)
{
	glViewport(0, 0, width, height);
}

void buttonCallback(long button, bool pressed)
{
	switch (button)
	{
	case VK_ESCAPE:
		window.close();
		break;
	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	rect.render();
}

int main()
{
	window.setResizeCallback(resize);
	window.setButtonCallback(buttonCallback);
	window.createWindow("OpenGL test window", 800, 600, { 0L, 0L });
	window.setCoreOpenGL();  // use to disable all deprecated functionality and use only core OpenGL
	if (!window.isOk())
		return EXIT_FAILURE;
	init();
	window.setRenderFunction(render);
	return window.loop();
}
