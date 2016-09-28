#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <engine/engine2d.hpp>
#include <engine/engine3d.hpp>


unsigned window_width = 800;
unsigned window_height = 600;

int last_frame_time;

using namespace engine;

Renderer2D* renderer2d;
Renderer3D* renderer3d;
Camera* camera;
Scene2D* scene2d;
Scene3D* scene3d;
DirectionalLight* dir_light;
PointLight* point_light;
SpotLight* spot_light;
Rectangle* rect;
Plane* plane;
Box* box;
BasicMaterial* basic_tile_material;
Material* box_material, * tile_material;
Texture* box_texture, * tile_texture;
Font* font;

float counter;
bool button_pressed[128];
int last_mouse_x, last_mouse_y;


void resize(unsigned int width, unsigned int height)
{
	window_width = width;
	window_height = height;
	renderer2d->setContextWidth(width, height);
	renderer3d->setContextWidth(width, height);
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

void draw(void)
{
	int current_time = glutGet(GLUT_ELAPSED_TIME);
	int fps = (int) round(1000.f / (current_time - last_frame_time));
	last_frame_time = current_time;

	std::string title = " FPS: " + std::to_string(fps);
	glutSetWindowTitle(title.c_str());

	updateCameraPosition();
	rect->rotate(glm::radians(1.f));
	auto scale = (sin(counter) + 2.f) / 3.f;
	rect->setScale({ scale, scale });
	box->setScale({ scale, scale, scale });
	box->rotate({ 0.f, glm::radians(1.f), 0.f });
	counter += 0.01f;

	renderer3d->clearScreen();

	scene3d->render();

	scene2d->render();
	font->renderText("test");
	glutSwapBuffers();
}

void setup()
{
	Config::getInstance().initializeLogger(
			std::cout.rdbuf()); // initializing logger with stdout as output stream
//    Config::getInstance().initializeLogger(); // initializing logger with default log file path
	try
	{
		renderer2d = new Renderer2D(window_width, window_height);
		renderer3d = new Renderer3D(window_width, window_height);
	}
	catch (std::exception& e)
	{
		Config::getInstance().logError(e.what());
		exit(EXIT_FAILURE);
	}

	try
	{
		box_texture = Texture::loadFromFile("res/box.jpg");
		tile_texture = Texture::loadFromFile("res/tile.jpg");
	}
	catch (FileNotFoundException& e)
	{
		Config::getInstance().logError(e.what());
	}

	// 2D
	rect = new Rectangle({ 300.f, 300.f }, { 400.f, 300.f }, { 150.f, 150.f });
	basic_tile_material = new BasicMaterial(renderer2d->getShaderProgram());
	basic_tile_material->setDiffuse(tile_texture);
	rect->setMaterial(basic_tile_material);
	scene2d = new Scene2D(renderer2d);
	scene2d->addEntity(rect);

	// 3D
	box_material = new Material();
	box_material->setDiffuse(box_texture);
	box_material->setAmbient(box_texture);
	tile_material = new Material();
	tile_material->setDiffuse(tile_texture);
	tile_material->setShininess(32);
	box = new Box({ 5.f, 5.f, 5.f }, { 20.f, 2.5f, 10.f });
	box->setPivot({ 2.5f, 2.5f, 2.5f });
	box->setMaterial(box_material);
	plane = new Plane({ 200.f, 200.f }, { -100.f, 0.f, -100.f }, 100);
	plane->setMaterial(tile_material);
	scene3d = new Scene3D(renderer3d);
	camera = new Camera({ 0.f, 5.f, 10.f }, { glm::radians(-45.f), 0.f, 0.f });
	scene3d->setCamera(camera);
	scene3d->addEntity(box);
	scene3d->addEntity(plane);
	dir_light = new DirectionalLight({ -1.f, -1.f, -1.f });
	point_light = new PointLight({ 50.f, 2.f, 50.f }, 10.f);
	spot_light = new SpotLight({ 10.f, 10.f, 10.f }, { -1.f, -1.f, -1.f }, 50.f, glm::radians(20.f),
	                                   glm::radians(5.f));
	scene3d->addLight(dir_light);
	scene3d->addLight(point_light);
	scene3d->addLight(spot_light);

	try
	{
		scene3d->loadFromFile("res/aventador/Avent.obj");
		scene3d->loadFromFile("res/cube.obj");
	}
	catch (FileNotFoundException& e)
	{
		Config::getInstance().logError(e.what());
	}

	font = Font::loadFromFile("res/comic_sans.ttf");

	draw();
	Config::getInstance().logErrors(); // checking if any errors were raised
}

void cleanup()
{
	delete renderer2d;
	delete renderer3d;
	delete scene2d;
	delete camera;
	delete dir_light;
	delete point_light;
	delete spot_light;
	delete scene3d;
}

void keyboard(unsigned char key, int x, int y)
{
	button_pressed[toupper(key)] = true;
	if (key == 27)
		glutLeaveMainLoop();
}

void keyboard_up(unsigned char key, int x, int y)
{
	button_pressed[toupper(key)] = false;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		last_mouse_x = x;
		last_mouse_y = y;
	}
}

void mouse_move(int x, int y)
{
	int rotate_x = y - last_mouse_y;
	int rotate_y = last_mouse_x - x;
	camera->rotate({ rotate_x / 200.f, rotate_y / 200.f, 0.f });
	last_mouse_x = x;
	last_mouse_y = y;
}

void idle()
{
	int delay = (int) round(1000.f / 60.f) - (glutGet(GLUT_ELAPSED_TIME) - last_frame_time);
	if (delay > 0)
		usleep((unsigned) delay * 1000);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitContextVersion(4, 1);
	glutInitContextFlags(GLUT_DEBUG);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("");

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	if (glGetError() == GL_INVALID_ENUM)
		std::cout << "GL_INVALID_ENUM on glewInit()" << std::endl;

	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutReshapeFunc((void (*)(int, int)) resize);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_move);

	setup();
	glutMainLoop();
	cleanup();
	return 0;
}
