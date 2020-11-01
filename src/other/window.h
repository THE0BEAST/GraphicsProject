/*

	As GLUT only supports displaying of 1 window at a time this class was made in such a way as to abstract it's functionality in a class.
	This was achieved by instead of using a an object oriented object class or cramming all the code in the main function a purely
	static class was created that performs all the required window functionality but doesen't allot for creation of more than 1 
	instance of a window.

*/

#pragma once
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Camera.h"
#include "graphics/Renderer.h"
#include "math/Time.h"


enum KeyState
{
	Down, Up
};

class Window
{
private:
	static Renderer *renderer;
	static Camera *camera;
	static Light *light;
	static Vector2 resolution;
	static void(*inputCallback)(int key, KeyState state);
	static void(*updateFunc)();
	static GLuint vertexArrayObj;

public:
	static Vector2 mousePos;

	Window::Window();
	static void Init(int argc, char* argv[], const Vector2 resolution, const char* title, void(*inputCallback)(int key, KeyState state), void(*updateFunc)());
	static void Update();
	static Vector2 GetSize();
	static Renderer* GetRenderer();
	static Camera* GetCamera();
	static Light* GetLight();
	static void Add(Model3D *object);
	static void KeyDown(unsigned char key, int x, int y);
	static void KeyUp(unsigned char key, int x, int y);
	static void MouseInput(int button, int state, int x, int y);
	static void MouseMove(int x, int y);
	static void NextObject();
};

