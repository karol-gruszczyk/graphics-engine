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
bool initialization_done = false;
std::chrono::steady_clock::time_point last_frame_time;

using namespace bauasian;

Renderer2D* renderer2d;
Renderer3D* renderer3d;
Camera* camera;
Scene2D* scene2d, * loading_scene;
Scene3D* scene3d;
Rectangle* rect, * loading_rect;
Plane* plane;
Box* box;
BasicMaterial* basic_tile_material;
Material* box_material, * tile_material;
Texture* box_texture, * tile_texture;
Text* fps_text, * stat_text, * loading_text;

float counter;
bool mouse_button_pressed;
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
		usleep((unsigned) delay);
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
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
		const double rotate_y = last_mouse_x - x;
		camera->rotate({ rotate_x / 200.f, rotate_y / 200.f, 0.f });
	}
	last_mouse_x = x;
	last_mouse_y = y;
}

void updateCameraPosition()
{
	const float speed = 1.f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRight(-speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRight(speed);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveForward(speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveForward(-speed);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->rotate({ 0.f, 0.f, -0.01f });
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->rotate({ 0.f, 0.f, 0.01f });
}

void draw(void)
{
	glfwPollEvents();
	calc_fps();
	std::string title = "fps: " + std::to_string(fps);
	fps_text->setText(title);

	updateCameraPosition();
	rect->rotate(glm::radians(1.f));
	auto scale = (sin(counter) + 2.f) / 3.f;
	rect->setScale({ scale, scale });
	box->setScale({ scale, scale, scale });
	box->rotate({ 0.f, glm::radians(1.f), 0.f });
	counter += 0.01f;

	renderer3d->clearScreen();

	renderer3d->render(scene3d);

	renderer2d->render(scene2d);
	fps_text->render();
	stat_text->render();
	idle();
	glfwSwapBuffers(window);
}

void setup()
{
	renderer3d = new Renderer3D();
	renderer3d->setZFar(10000);
	//renderer3d->addFilter(new KernelFilter(KernelFilter::GRADIENT_DETECTION_VERTICAL));
	//renderer3d->addFilter(new LargeKernelFilter(LargeKernelFilter::GAUSSIAN_BLUR));

	try
	{
		tile_texture = TextureFactory::getInstance().getTexture("res/tile.jpg");
	}
	catch (FileNotFoundException& e)
	{
		Bauasian::getInstance().logError(e.what());
	}

	// 2D
	rect = new Rectangle(glm::vec2(300.f, 300.f));
	rect->setPosition({ 400.f, 300.f });
	rect->setPivot({ 150.f, 150.f });
	basic_tile_material = new BasicMaterial(tile_texture);
	rect->setMaterial(basic_tile_material);
	scene2d = new Scene2D();
	//scene2d->addEntity(rect);

	// 3D
	box_material = new Material();
	box_material->setDiffuse(TextureFactory::getInstance().getTexture("res/planks.jpg"));
	box_material->setAmbient(TextureFactory::getInstance().getTexture("res/planks.jpg"));
	box_material->setNormalTexture(TextureFactory::getInstance().getTexture("res/planks_normal.jpg"));
	tile_material = new Material();
	tile_material->setAmbient(tile_texture);
	tile_material->setDiffuse(tile_texture);
	tile_material->setShininess(32);
	box = new Box(glm::vec3(5.f, 5.f, 5.f));
	box->setPosition({ 20.f, 2.5f, 10.f });
	box->setPivot({ 2.5f, 2.5f, 2.5f });
	box->setMaterial(box_material);
	plane = new Plane({ 200.f, 200.f }, 100);
	plane->setPosition({ -100.f, 0.f, -100.f });
	plane->setMaterial(tile_material);
	scene3d = new Scene3D();
	scene3d->addEntity(box);
	scene3d->addEntity(plane);
	DirectionalLight dir_light(glm::vec3(-1.f, -1.f, -1.f));
	PointLight point_light({ 50.f, 2.f, 50.f }, 10.f);
	SpotLight spot_light({ 10.f, 10.f, 10.f }, { -1.f, -1.f, -1.f }, 50.f, glm::radians(20.f), glm::radians(25.f));
	scene3d->addLight(dir_light);
	scene3d->addLight(point_light);
	scene3d->addLight(spot_light);

	try
	{
		//scene3d->loadFromFile("res/sibenik/sibenik.obj");
		//scene3d->loadFromFile("res/Damaged Downtown/Downtown_Damage_0.obj");
		//scene3d->loadFromFile("res/Damaged Downtown/Downtown_Damage_1.obj");
		//scene3d->loadFromFile("res/Damaged Downtown/Downtown_Damage_2.obj");
		//scene3d->loadFromFile("res/sponza/sponza.obj");
		//scene3d->loadFromFile("res/crytek/sponza2.obj");
		//scene3d->loadFromFile("res/pabellon/pavillon_barcelone_v1.2.blend");
		//scene3d->loadFromFile("res/Medieval/Medieval_City.obj", false);
		scene3d->loadFromFile("res/aerial_landscape_v1.0.blend", true);
	}
	catch (FileNotFoundException& e)
	{
		Bauasian::getInstance().logError(e.what());
	}
	scene3d->addCamera(new Camera({ 0.f, 5.f, 10.f }, { glm::radians(-45.f), 0.f, 0.f }));
	camera = scene3d->getCamera();

	fps_text = new Text(FontFactory::getInstance().getFont("res/comic_sans.ttf", 14));
	fps_text->setPosition({ 0, 14 });
	fps_text->setTextColor({ 1.f, 1.f, 0.f });
	auto text = "vertices: " + std::to_string(scene3d->getNumVertices()) +
	            "\nfaces: " + std::to_string(scene3d->getNumFaces()) +
	            "\nentities: " + std::to_string(scene3d->getNumMeshes());
	stat_text = new Text(FontFactory::getInstance().getFont("res/comic_sans.ttf", 14), text);
	stat_text->setPosition({ 0, 32 });
	stat_text->setTextColor({ 1.f, 1.f, 1.f });

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
	initialization_done = true;
}

void cleanup()
{
	delete renderer2d;
	delete renderer3d;
	delete scene2d;
	delete scene3d;
	delete fps_text;
	delete stat_text;
	delete loading_scene;
}

void setup_loading()
{
	renderer2d = new Renderer2D();
	loading_rect = new Rectangle(glm::vec2(150.f, 150.f));
	loading_rect->setPosition({ 400.f, 300.f });
	loading_rect->setPivot({ 75.f, 75.f });

	auto loading_material = new BasicMaterial(TextureFactory::getInstance().getTexture("res/loading.png"));
	loading_rect->setMaterial(loading_material);
	loading_scene = new Scene2D();
	loading_scene->addEntity(loading_rect);

	loading_text = new Text(FontFactory::getInstance().getFont("res/unispace bd.ttf", 25), "Loading scene ...");
	loading_text->setPosition({ 300, 420 });
	loading_text->setTextColor({ 1.f, 1.f, 1.f });
}

void draw_loading()
{
	glfwPollEvents();
	calc_fps();
	renderer2d->clearScreen();
	renderer2d->render(loading_scene);
	loading_rect->rotate(glm::radians(5.f));
	loading_text->render();
	idle();
	glfwSwapBuffers(window);
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

	setup_loading();
	setup();

	while (!glfwWindowShouldClose(window) && !initialization_done)
		draw_loading();

	while (!glfwWindowShouldClose(window))
		draw();

	glfwTerminate();
	cleanup();
	return EXIT_SUCCESS;
}
