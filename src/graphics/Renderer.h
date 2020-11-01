#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Shader.h"
#include "other/Light.h"
#include "other/Camera.h"
#include "graphics/Model3D.h"
#include "math/Vector2.h"
#include "Utils/FileReaders.h"

class Renderer
{
private:
	std::vector<Model3D*> renderables; // Objects that are currently being drawn
	int currentlyRendered = 0;
	Camera *camera;
	Light *light;
	Vector2 screenSize;
	Shader *shader;
public:
	Renderer();
	Renderer(Camera *camera, const Vector2 screenSize, Light *light);
	void Render();
	void Submit(Model3D *renderable);
	void NextObject();

	void Renderer::SetupShaders();
};

