#include <iostream>
#include <engine/renderers/renderer_2d.h>
#include <engine/renderers/renderer_3d.h>
#include <engine/renderers/scene_2d.h>
#include <engine/renderers/scene_3d.h>
#include <engine/camera.h>
#include <engine/config.h>
#include <engine/primitives/rectangle.h>
#include <engine/primitives/plane.h>
#include <engine/primitives/box.h>
#include <engine/texture.h>
#include "win_api_window.h"

unsigned window_width = 800;
unsigned window_height = 600;

WinApiWindow window;
std::string gl_version;
engine::Renderer2D* renderer2d;
engine::Renderer3D* renderer3d;
engine::Camera* camera;
engine::Scene2D* scene2d;
engine::Scene3D* scene3d;
engine::DirectionalLight* dir_light;
engine::PointLight* point_light;
engine::SpotLight* spot_light;
engine::Rectangle* rect;
engine::Plane* plane;
engine::Box* box;
engine::Texture* box_texture, * tile_texture;

float counter;
bool button_pressed[128];

void resize(long width, long height)
{
	window_width = width;
	window_height = height;
	renderer2d->setContextWidth(width, height);
	renderer3d->setContextWidth(width, height);
}

void mouseMoveCallback(long x, long y)
{
	long delta_x = window_height / 2 - y;
	long delta_y = x - window_width / 2;
	if (delta_x || delta_y)
	{
		camera->rotate({ delta_x / 200.f, delta_y / 200.f, 0.f });
		window.setCursorPosition(window_width / 2, window_height / 2);
	}
}

void buttonCallback(long button, bool pressed)
{
	button_pressed[button] = pressed;
	switch (button)
	{
	case VK_ESCAPE:
		window.close();
		break;
	}
}

void updateCameraPosition()
{
	if (button_pressed['A'])
		camera->moveRight(-0.5f);
	if (button_pressed['D'])
		camera->moveRight(0.5f);
	if (button_pressed['W'])
		camera->moveForward(0.5f);
	if (button_pressed['S'])
		camera->moveForward(-0.5f);
	if (button_pressed['Q'])
		camera->rotate({ 0.f, 0.f, -0.01f });
	if (button_pressed['E'])
		camera->rotate({ 0.f, 0.f, 0.01f });
}

void render()
{
	updateCameraPosition();
	rect->rotate(glm::radians(1.f));
	rect->setScale(sin(counter));
	counter += 0.01f;
	window.setTitle("OpenGL: " + gl_version + " FPS: " + std::to_string(window.getFPS()));

	renderer3d->clearScreen();

	box_texture->bind();
	scene3d->render();

	tile_texture->bind();
	plane->render();
	scene2d->render();
}

void cleanup()
{
	delete renderer2d;
	delete renderer3d;
	delete rect;
	delete scene2d;
	delete box;
	delete plane;
	delete camera;
	delete dir_light;
	delete point_light;
	delete spot_light;
	delete scene3d;
}

void init()
{
	window.setButtonCallback(buttonCallback);
	window.setMouseMoveCallback(mouseMoveCallback);
	window.setRenderFunction(render);
	window.setCleanupFunction(cleanup);
	window.createWindow("", window_width, window_height);
	window.setCoreOpenGL();  // use to disable all deprecated functionality and use only core OpenGL
	if (!window.isOk())
		exit(EXIT_FAILURE);
	window.setCursorPosition(window_width / 2, window_height / 2);

	gl_version = std::string((char*)glGetString(GL_VERSION));

	window.showConsole();
	engine::Config::getInstance().initializeLogger(std::cout.rdbuf()); // initializing logger with stdout as output stream
	//engine::Config::getInstance().initializeLogger(); // initializing logger with default log file path

	engine::Config::getInstance().setShaderPath("..\\..\\engine\\glsl\\");
	try
	{
		renderer2d = new engine::Renderer2D(window_width, window_height);
		renderer3d = new engine::Renderer3D(window_width, window_height);
	}
	catch (engine::ShaderCompileException&)
	{
		window.showConsole();
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	window.setResizeCallback(resize);

	rect = new engine::Rectangle({ 300.f, 300.f }, { 400.f, 300.f }, { 150.f, 150.f });
	scene2d = new engine::Scene2D(renderer2d);
	scene2d->addEntity(rect);

	box = new engine::Box({ 5.f, 5.f, 5.f });
	plane = new engine::Plane({ 200.f, 200.f }, { -100.f, 0.f, -100.f }, 100);
	scene3d = new engine::Scene3D(renderer3d);
	camera = new engine::Camera({ 0.f, 5.f, 10.f });
	scene3d->setCamera(camera);
	scene3d->addEntity(box);
	dir_light = new engine::DirectionalLight({ -1.f, -1.f, -1.f });
	point_light = new engine::PointLight({ 50.f, 2.f, 50.f }, 10.f);
	spot_light = new engine::SpotLight({ 10.f, 10.f, 10.f }, { -1.f, -1.f, -1.f }, 50.f, glm::radians(20.f), glm::radians(5.f));
	scene3d->addLight(dir_light);
	scene3d->addLight(point_light);
	scene3d->addLight(spot_light);
	try
	{
		box_texture = new engine::Texture("box.jpg");
		tile_texture = new engine::Texture("tile.jpg");
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
