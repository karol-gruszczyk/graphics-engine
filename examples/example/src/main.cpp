#include <iostream>
#include <chrono>
#include <boost/lexical_cast.hpp>
#include <engine/renderers/renderer_2d.h>
#include <engine/renderers/scene_2d.h>
#include <engine/config.h>
#include <engine/primitives/rectangle.h>
#include "win_api_window.h"

WinApiWindow window;
std::string gl_version;
engine::Renderer2D renderer;
engine::Scene2D scene;
engine::Rectangle rect;
float counter;

std::chrono::steady_clock::time_point last_time;
unsigned frames = 0;


void resize(long width, long height)
{
	renderer.setContextWidth(width, height);
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
	renderer.clearScreen();

	scene.render();
	rect.rotate(0.05);
	rect.setScale(sin(counter));
	counter += 0.0001f;
	auto current_time = std::chrono::high_resolution_clock::now();
	unsigned delta_time = (unsigned)std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();
	if (++frames > 0 && delta_time > 1000)
	{
		unsigned fps = unsigned(frames / (delta_time / 1'000.0));
		window.setTitle("OpenGL: " + gl_version + " FPS: " + boost::lexical_cast<std::string>(fps));
		last_time = current_time;
		frames = 0;
	}
}

void init()
{
	window.setButtonCallback(buttonCallback);
	window.setRenderFunction(render);
	window.createWindow("", 800, 600);
	window.setCoreOpenGL();  // use to disable all deprecated functionality and use only core OpenGL
	if (!window.isOk())
		exit(EXIT_FAILURE);

	gl_version = std::string((char*)glGetString(GL_VERSION));

	engine::Config::setShaderPath("..\\..\\engine\\glsl\\");
	engine::Config::initializeLogger();
	try
	{
		renderer.init(800, 600);
	}
	catch (engine::ShaderCompileException& e)
	{
		window.showConsole();
		std::cout << e.what() << std::endl;
		std::cout << e.getErrorMessage() << std::endl;
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	window.setResizeCallback(resize);

	rect.initialize({ 300.f, 300.f }, { 400.f, 300.f }, { 150.f, 150.f });
	scene.setRenderer(&renderer);
	scene.addEntity(&rect);

	last_time = std::chrono::high_resolution_clock::now();
}

int main()
{
	init();
	return window.loop();
}
