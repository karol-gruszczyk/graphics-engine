#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <bauasian/bauasian2d.hpp>
#include <bauasian/bauasian3d.hpp>


unsigned window_width = 800;
unsigned window_height = 600;

std::chrono::steady_clock::time_point last_frame_time;

using namespace bauasian;

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
Text* text;

float counter;
bool button_pressed[128];
int last_mouse_x, last_mouse_y;


void resize(unsigned int width, unsigned int height)
{
	window_width = width;
	window_height = height;
	Bauasian::getInstance().setContextSize({ width, height });
}

void updateCameraPosition()
{
	if (button_pressed['A'])
		camera->moveRight(-10.f);
	if (button_pressed['D'])
		camera->moveRight(10.f);
	if (button_pressed['W'])
		camera->moveForward(10.f);
	if (button_pressed['S'])
		camera->moveForward(-10.f);
	if (button_pressed['Q'])
		camera->rotate({ 0.f, 0.f, -0.01f });
	if (button_pressed['E'])
		camera->rotate({ 0.f, 0.f, 0.01f });
}

void draw(void)
{
	auto current_time = std::chrono::steady_clock::now();
	int fps = (int) round(1e+6 / std::chrono::duration_cast<std::chrono::microseconds>
			(current_time - last_frame_time).count());
	last_frame_time = current_time;

	std::string title = "FPS: " + std::to_string(fps);
	text->setText(title);

	updateCameraPosition();
	//rect->rotate(glm::radians(1.f));
	auto scale = (sin(counter) + 2.f) / 3.f;
	rect->setScale({ scale, scale });
	box->setScale({ scale, scale, scale });
	box->rotate({ 0.f, glm::radians(1.f), 0.f });
	counter += 0.01f;

	renderer3d->clearScreen();

	renderer3d->render(scene3d);

	renderer2d->render(scene2d);
	text->render();
	glutSwapBuffers();
}

void setup()
{
	Bauasian::getInstance().initializeLogger(
			std::cout.rdbuf()); // initializing logger with stdout as output stream
//    Bauasian::getInstance().initializeLogger(); // initializing logger with default log file path
	Bauasian::getInstance().setContextSize({ window_width, window_height });

	renderer2d = new Renderer2D();
	renderer3d = new Renderer3D();
	renderer3d->setZFar(10000);
	renderer3d->addFilter(new BlackWhiteFilter());
	renderer3d->addFilter(new KernelFilter(KernelFilter::GAUSSIAN_BLUR));
	renderer3d->addFilter(new KernelFilter(KernelFilter::EDGE_DETECTION));

	try
	{
		box_texture = Texture::loadFromFile("res/box.jpg");
		tile_texture = Texture::loadFromFile("res/tile.jpg");
	}
	catch (FileNotFoundException& e)
	{
		Bauasian::getInstance().logError(e.what());
	}

	// 2D
	rect = new Rectangle({ 300.f, 300.f }, { 400.f, 300.f }, { 150.f, 150.f });
	basic_tile_material = new BasicMaterial(renderer2d->getShaderProgram());
	basic_tile_material->setDiffuse(tile_texture);
	rect->setMaterial(basic_tile_material);
	scene2d = new Scene2D();
	//scene2d->addEntity(rect);

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
	scene3d = new Scene3D();
	camera = new Camera({ 0.f, 5.f, 10.f }, { glm::radians(-45.f), 0.f, 0.f });
	scene3d->setCamera(camera);
	//scene3d->addEntity(box);
	//scene3d->addEntity(plane);
	dir_light = new DirectionalLight({ -1.f, -1.f, -1.f });
	point_light = new PointLight({ 50.f, 2.f, 50.f }, 10.f);
	spot_light = new SpotLight({ 10.f, 10.f, 10.f }, { -1.f, -1.f, -1.f }, 50.f, glm::radians(20.f),
	                           glm::radians(5.f));
	scene3d->addLight(dir_light);
	scene3d->addLight(point_light);
	scene3d->addLight(spot_light);

	try
	{
		//scene3d->loadFromFile("res/aventador/Avent.obj");
		scene3d->loadFromFile("res/cs_office.obj");
	}
	catch (FileNotFoundException& e)
	{
		Bauasian::getInstance().logError(e.what());
	}

	text = new Text(Font::loadFromFile("res/comic_sans.ttf", 14));
	text->setPosition({ 0, 14 });
	text->setTextColor({ 1.f, 1.f, 1.f });

	draw();
	Bauasian::getInstance().checkErrors(); // checking if any errors were raised
}

void cleanup()
{
	delete renderer2d;
	delete renderer3d;
	delete scene2d;
	delete camera;
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
	int delay = (int) round(1e+6 / 60.f - std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::steady_clock::now() - last_frame_time).count());
	if (delay > 0)
		usleep((unsigned) delay);
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
	glutSetWindowTitle((std::string("OpenGL ") + (char*)glGetString(GL_VERSION)).c_str());

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
	return EXIT_SUCCESS;
}
