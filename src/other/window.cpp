/*

As GLUT only supports displaying of 1 window at a time this class was made in such a way as to abstract it's functionality in a class.
This was achieved by instead of using a an object oriented object class or cramming all the code in the main function a purely
static class was created that performs all the required window functionality but doesen't allot for creation of more than 1
instance of a window.

*/

#include "Window.h"

Renderer *Window::renderer;
Camera *Window::camera;
Light *Window::light;
Vector2 Window::resolution;
void(*Window::inputCallback)(int key, KeyState state);
void(*Window::updateFunc)();

Vector2 Window::mousePos;

Window::Window()
{
	std::cout << "This class does not need to be instantiated, use Window::Init() instead!";
}

void Window::Init(int argc, char* argv[], const Vector2 resolution, const char* title, void(*inputCallback)(int key, KeyState state), void(*updateFunc)())
{
	Window::resolution = resolution;

	glutInit(&argc, argv);
	glutInitWindowSize(resolution.x, resolution.y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(title);
	glutDisplayFunc(Update);

	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MouseMove);

	Window::inputCallback = inputCallback;
	Window::updateFunc = updateFunc;

	GLenum err = glewInit();
	if (GLEW_OK != err)
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	Window::camera = new Camera(Vector3(0.0, 0.0, 5.0), Vector3::Zero(), Vector3::Up());
	Window::light = new Light(Vector3(0.0, 1.0, 10.0), Vector3(1.0, 1.0, 1.0), Vector3(0.3, 0.3, 0.3));
	Window::renderer = new Renderer(camera, resolution, Window::light);
}

void Window::Update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Time::UpdateDeltaTime();
	renderer->Render();

	glutSwapBuffers();
	glutPostRedisplay();

	updateFunc();
}

Vector2 Window::GetSize()
{
	return resolution;
}

Renderer* Window::GetRenderer()
{
	return renderer;
}

Camera* Window::GetCamera()
{
	return camera;
}

Light* Window::GetLight()
{
	return light;
}

void Window::Add(Model3D *object)
{
	renderer->Submit(object);
}

void Window::KeyDown(unsigned char key, int x, int y)
{
	inputCallback(key, KeyState::Down);
}

void Window::KeyUp(unsigned char key, int x, int y)
{
	inputCallback(key, KeyState::Up);
}

void Window::MouseInput(int button, int state, int x, int y)
{
	mousePos.x = x;
	mousePos.y = y;

	inputCallback((unsigned char)button, KeyState(state));
}

void Window::MouseMove(int x, int y)
{
	mousePos.x = x;
	mousePos.y = y;
}

void Window::NextObject()
{
	renderer->NextObject();
}