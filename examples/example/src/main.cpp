#include <iostream>
#include <boost/lexical_cast.hpp>
#include <engine/renderers/renderer_2d.h>
#include <engine/renderers/scene_2d.h>
#include <engine/config.h>
#include <engine/primitives/rectangle.h>
#include "win_api_window.h"
#include <engine/texture.h>

WinApiWindow window;
std::string gl_version;
engine::Renderer2D renderer;
engine::Scene2D scene;
engine::Rectangle rect;
engine::Texture texture;
float counter;


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
	texture.bind();

	scene.render();
	rect.rotate(1.f);
	rect.setScale(sin(counter));
	counter += 0.01f;
	window.setTitle("OpenGL: " + gl_version + " FPS: " + boost::lexical_cast<std::string>(window.getFPS()));
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

	window.showConsole();
	engine::Config::getInstance().initializeLogger(std::cout.rdbuf()); // initializing logger with stdout as output stream
	//engine::Config::getInstance().initializeLogger(); // initializing logger with default log file path

	engine::Config::getInstance().setShaderPath("..\\..\\engine\\glsl\\");
	try
	{
		renderer.init(800, 600);
	}
	catch (engine::ShaderCompileException&)
	{
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	window.setResizeCallback(resize);

	rect.initialize({ 300.f, 300.f }, { 400.f, 300.f }, { 150.f, 150.f });
	scene.setRenderer(&renderer);
	scene.addEntity(&rect);
	try
	{
		texture.loadFromFile("moto.jpg");
	}
	catch (engine::FileNotFoundException& e)
	{
		engine::Config::getInstance().log(e.what());
	}

	render();
	engine::Config::getInstance().logErrors(); // checking if any errors were raised
}

int main()
{
	init();
	return window.loop();
}
