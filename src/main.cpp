/*
 *	Author: Edgaras Zelencovas
 *	Task: Assignment 1 - Photo-Realistic Image Generation Using Ray Casting/Tracing
 *	Module: Graphics 2
 *	Lecturer: Dr. Yinghui Zhang
 */
#include <math.h>
#include <iomanip>
#include <GL/glew.h>

#include "other/Window.h"
#include "graphics/Texture.h"
#include "math/TorusGenerator.h"
#include "math/Time.h"

Model3D *object1, *object2, *object3, *object4;
Material *material1, *material2, *material3;
int currentMaterial = 0;

bool rotate = false, rotateWithMouse = false;

void Update() // Called every frame
{
	std::cout << std::fixed << std::setprecision(1) << "\rFramerate: " << std::setfill('0') << std::setw(4) << Time::FrameRate();

	if (rotate)
	{
		object1->Rotate(Vector3(0, 1, 0), 30 * Time::DeltaTime());
		object2->Rotate(Vector3(1, 0, 0), 30 * Time::DeltaTime());
		object3->Rotate(Vector3(1, 0, 0), 30 * Time::DeltaTime());
		object4->Rotate(Vector3(1, 0, 0), 30 * Time::DeltaTime());
	}
	if (rotateWithMouse)
	{
		Vector2 direction2D = (Window::mousePos - Window::GetSize() / 2).Normalized();
		object1->Rotate(Vector3(-direction2D.y, -direction2D.x, 0), 30 * Time::DeltaTime());
		object2->Rotate(Vector3(-direction2D.y, -direction2D.x, 0), 30 * Time::DeltaTime());
		object3->Rotate(Vector3(-direction2D.y, -direction2D.x, 0), 30 * Time::DeltaTime());
		object4->Rotate(Vector3(-direction2D.y, -direction2D.x, 0), 30 * Time::DeltaTime());
	}
}

void inputCallback(int key, KeyState state) // User input callback
{
	if (state == KeyState::Down)
	{
		switch (key)
		{
			case 'q': // Zoom in
				Window::GetCamera()->position.z += 1; 
				break;
			case 'a': // Zoom out
				if (Window::GetCamera()->position.z > 1)
					Window::GetCamera()->position.z -= 1;
				break;
			case 'r': // Turn on object rotation
				rotate = !rotate; 
				break;
			case 't': // Show next object
				Window::NextObject(); 
				break;
			case 'e': // Show next material
				++currentMaterial;
				if (currentMaterial >= 3)
					currentMaterial = 0;
				if (currentMaterial == 0)
				{
					object1->material = material1;
					object2->material = material1;
					object3->material = material1;
					object4->material = material1;
				}
				else if (currentMaterial == 1)
				{
					object1->material = material2;
					object2->material = material2;
					object3->material = material2;
					object4->material = material2;
				}
				else if (currentMaterial == 2)
				{
					object1->material = material3;
					object2->material = material3;
					object3->material = material3;
					object4->material = material3;
				}
				break;
			case 'w': // Increase light intensity
				Window::GetLight()->IncreaseIntensity(0.1f);
				break;
			case 's': // Decrease light intensity
				Window::GetLight()->DecreaseIntensity(0.1f);
				break;
			case 0: // Start mouse rotation
				rotateWithMouse = true;
				break;
			default:
				break;
		}
	}
	else if (state == KeyState::Up)
	{
		switch (key)
		{
			case 0: // Stop mouse rotation
				rotateWithMouse = false;
				break;
			default:
				break;
		}
	}
}

void main(int argc, char* argv[])
{
	try
	{
		Window::Init(argc, argv, Vector2(800, 600), "Assignment 1", inputCallback, Update); // Initialize window

		std::cout << "[VERSION]" << std::endl;
		std::cout << "GLUT version: " << GLUT_API_VERSION << std::endl;
		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << std::endl;
		std::cout << "[CONTROLS]" << std::endl;
		std::cout << "R - Start / Stop rotation" << std::endl;
		std::cout << "T - Change shown model" << std::endl;
		std::cout << "E - Change material" << std::endl;
		std::cout << "Q/A - Zoom out / Zoom in" << std::endl;
		std::cout << "W/S - Increase / Decrease light intensity " << std::endl;
		system("pause");

		// Initialize Objects
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> uvs;
		TorusGenerator::GenerateTorusVertices(vertices, normals, uvs, 1, 1.0f, 0.3f);
		object1 = new Model3D(vertices, normals, uvs);
		object2 = new Model3D("Resources/Models/Cube.obj");
		object3 = new Model3D("Resources/Models/Icosphere.obj");
		object4 = new Model3D("Resources/Models/Car.obj");

		// Initialize materials
		material1 = new Material("Resources/Textures/texture1.bmp");
		material2 = new Material("Resources/Textures/texture2.bmp");
		material3 = new Material("Resources/Textures/texture3.bmp");

		// Add textures to spheres
		object1->material = material1;
		object2->material = material1;
		object3->material = material1;
		object4->material = material1;

		// Add Objects to the window/renderer
		Window::Add(object1);
		Window::Add(object2);
		Window::Add(object3);
		Window::Add(object4);

		glutMainLoop();
		system("pause");
		return;
	}
	catch (char* e)
	{
		std::cout << "Runtime Error: " << e << std::endl;
		system("pause");
		exit(1);
	}
}