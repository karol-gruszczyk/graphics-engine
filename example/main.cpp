#include <iostream>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <bauasian/bauasian2d.hpp>
#include <bauasian/bauasian3d.hpp>


GLFWwindow* window, * offscreen_window;
unsigned window_width = 800;
unsigned window_height = 600;

int fps = 0;
std::chrono::steady_clock::time_point last_frame_time;

using namespace bauasian;

DeferredRenderer* renderer;
Camera* camera;
Scene3D* scene3d;
Text* fps_text, * stat_text;
SunSkyBox* sky_box;
DirectionalLight* dir_light;

float counter;
bool mouse_button_pressed, accelerate, wireframe, button_pressed[128];
double last_mouse_x, last_mouse_y;


void calc_fps()
{
	auto current_time = std::chrono::steady_clock::now();
	fps = (int) round(1e+6 / std::chrono::duration_cast<std::chrono::microseconds>
			(current_time - last_frame_time).count());
	last_frame_time = current_time;
}

void idle()
{
	int delay = (int) round(1e+6 / 60.f - std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::steady_clock::now() - last_frame_time).count());
	if (delay > 0)
		std::this_thread::sleep_for(std::chrono::microseconds(delay));
}

void error_callback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	window_width = (unsigned) width;
	window_height = (unsigned) height;
	Bauasian::getInstance().setContextSize({ width, height });
//	camera->setAspectRatio((float) width / height);
	renderer->setSize({ width, height });
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_KP_ADD)
		renderer->setExposure(renderer->getExposure() + 0.01f);
	else if (key == GLFW_KEY_KP_SUBTRACT)
		renderer->setExposure(std::max(renderer->getExposure() - 0.1f, 0.01f));
	else if (key == GLFW_KEY_KP_9)
		counter += 0.01f;
	else if (key == GLFW_KEY_KP_3)
		counter -= 0.01f;

	if (action == GLFW_REPEAT)
		return;

	button_pressed[key] = action == GLFW_PRESS;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_LEFT_SHIFT)
		accelerate = action == GLFW_PRESS;
	else if (key == GLFW_KEY_F3)
	{
		if (action == GLFW_PRESS)
		{
			wireframe = !wireframe;
			Bauasian::getInstance().setWireframe(wireframe);
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			mouse_button_pressed = true;
		else if (action == GLFW_RELEASE)
			mouse_button_pressed = false;
	}
}

void mouse_pos_callback(GLFWwindow* window, double x, double y)
{
	if (mouse_button_pressed)
	{
		const double rotate_x = y - last_mouse_y;
		const double rotate_y = x - last_mouse_x;
		camera->pitch((float) rotate_x / 200.f);
		camera->rotate((float) rotate_y / 200.f, glm::vec3(0.f, 1.f, 0.f));
	}
	last_mouse_x = x;
	last_mouse_y = y;
}

void updateCameraPosition()
{
	float speed = 1.f;
	if (accelerate)
		speed *= 20.f;
	glm::vec3 delta_pos;
	if (button_pressed[GLFW_KEY_A])
		delta_pos += camera->getRight() * -speed;
	if (button_pressed[GLFW_KEY_D])
		delta_pos += camera->getRight() * speed;
	if (button_pressed[GLFW_KEY_W])
		delta_pos += camera->getDirection() * speed;
	if (button_pressed[GLFW_KEY_S])
		delta_pos += camera->getDirection() * -speed;
	if (button_pressed[GLFW_KEY_Q])
		camera->roll(-0.01f);
	if (button_pressed[GLFW_KEY_E])
		camera->roll(0.01f);
	camera->move(delta_pos);
}

void draw(void)
{
	glfwPollEvents();
	calc_fps();
	std::string title = "fps: " + std::to_string(fps);
	fps_text->setText(title);

	updateCameraPosition();

	glm::vec3 light_direction(glm::cos(counter), sin(counter), glm::cos(counter));
	dir_light->setDirection(light_direction);
	sky_box->setLightDirection(light_direction);

	renderer->clearScreen();
	renderer->render(scene3d);

	fps_text->render();
	stat_text->render();
	idle();
	glfwSwapBuffers(window);
}

void setup()
{
	renderer = new DeferredRenderer(glm::uvec2(window_width, window_height));
	renderer->addPostProcessor(new FXAA(renderer->getSize()));

	dir_light = new DirectionalLight(glm::vec3(-1.f, -0.3f, -1.f));
	PointLight* point_light = new PointLight({ 50.f, 2.f, 50.f }, 10.f);
	SpotLight* spot_light = new SpotLight({ 10.f, 10.f, 10.f }, { -1.f, -1.f, -1.f }, 50.f, glm::radians(20.f),
										  glm::radians(25.f));

	const std::string prefix("res/cube_textures/ashcanyon_");
	//const std::string prefix("res/cube_textures/interstellar_");
	const std::vector<boost::filesystem::path> paths = { prefix + "ft.tga", prefix + "bk.tga",
														 prefix + "dn.tga", prefix + "up.tga",
														 prefix + "rt.tga", prefix + "lf.tga", };
	//sky_box = new TexturedSkyBox(TextureFactory::getInstance().getCubeTexture(paths));
	//sky_box = new TexturedSkyBox(TextureFactory::getInstance().getCubeTexture("res/cube_textures/skybox.jpg"));
	sky_box = new SunSkyBox(dir_light->getDirection());

	scene3d = new Scene3D(sky_box);
	scene3d->addLight(dir_light);
	scene3d->addLight(point_light);
	scene3d->addLight(spot_light);

	scene3d->loadFromFile("scenes/sponza/sponza.obj", false, true);
//	scene3d->loadFromFile("scenes/dragon.obj");

	camera = new PerspectiveCamera(8.f / 6.f);
	camera->lookAt(glm::vec3(25.f, 25.f, 25.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	scene3d->addCamera(camera);

	camera = scene3d->getCamera();
	camera->setFar(10000.f);

	fps_text = new Text(FontFactory::getInstance().getFont("scenes/liberation.ttf", 14));
	fps_text->setPosition({ 0, 14 });
	fps_text->setTextColor({ 1.f, 1.f, 0.f });
	auto text = "vertices: " + std::to_string(scene3d->getNumVertices()) +
				"\nfaces: " + std::to_string(scene3d->getNumFaces()) +
				"\nentities: " + std::to_string(scene3d->getNumMeshes());
	stat_text = new Text(FontFactory::getInstance().getFont("scenes/liberation.ttf", 14), text);
	stat_text->setPosition({ 0, 32 });
	stat_text->setTextColor({ 1.f, 1.f, 1.f });

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
}

void cleanup()
{
	delete renderer;
	delete scene3d;
	delete fps_text;
	delete stat_text;
	delete sky_box;
}

int main(int argc, char** argv)
{
	glfwInit();
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window = glfwCreateWindow(window_width, window_height, "", nullptr, nullptr);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	offscreen_window = glfwCreateWindow(640, 480, "", nullptr, window);

	glfwMakeContextCurrent(window);
	if (!window || !offscreen_window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwSetWindowPos(window, 50, 50);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	if (glGetError() == GL_INVALID_ENUM)
		std::cout << "GL_INVALID_ENUM on glewInit()" << std::endl;
	glfwSetWindowTitle(window, (std::string("OpenGL ") + (char*) glGetString(GL_VERSION)).c_str());

	Bauasian::getInstance().initialize(std::cout.rdbuf(), std::cerr.rdbuf());
	//Bauasian::getInstance().initialize();
	Bauasian::getInstance().setContextSize({ window_width, window_height });

	setup();

	while (!glfwWindowShouldClose(window))
		draw();

	glfwTerminate();
	cleanup();
	return EXIT_SUCCESS;
}
