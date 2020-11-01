#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::Renderer(Camera *camera, const Vector2 screenSize, Light *light) : camera(camera), screenSize(screenSize), light(light)
{
	SetupShaders();
}

void Renderer::SetupShaders()
{
	glEnable(GL_DEPTH_TEST);

	shader = new Shader("Resources/Shaders/vertshader.vert", "Resources/Shaders/fragshader.frag");
	shader->Enable();


	std::cout << "[SHADERS]" << std::endl;
	std::cout << "Shaders sucessfuly installed" << std::endl << std::endl;
}

void Renderer::Render()
{
	GLuint VAO;
	GLuint VBO[3];

	glGenBuffers(3, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, renderables[currentlyRendered]->vertices.size() * sizeof(Vector3), &renderables[currentlyRendered]->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, renderables[currentlyRendered]->normals.size() * sizeof(Vector3), &renderables[currentlyRendered]->normals[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, renderables[currentlyRendered]->uvs.size() * sizeof(Vector2), &renderables[currentlyRendered]->uvs[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindVertexArray(VAO);

	Matrix4x4 modelMatrix = renderables[currentlyRendered]->GetModelMatrix();
	Matrix4x4 viewMatrix = camera->GetViewMatrix();
	Matrix4x4 projectionMatrix = Matrix4x4::Perspective(45.0f, screenSize.x / screenSize.y, 1.0f, 100.0f);

	Matrix4x4 MV = modelMatrix * viewMatrix;
	Matrix4x4 MVP = modelMatrix * viewMatrix * projectionMatrix;

	shader->AttachUniformMatrix4f("MV", MV);
	shader->AttachUniformMatrix4f("MVP", MVP);
	shader->AttachUniformMatrix4f("viewMatrix", viewMatrix);

	shader->AttachUniformLight(light);
	shader->AttachUniformMaterial(renderables[currentlyRendered]->material);

	glDrawArrays(GL_TRIANGLES, 0, renderables[currentlyRendered]->vertices.size());

	glDeleteBuffers(3, VBO);   
}

void Renderer::Submit(Model3D *renderable)
{
	renderables.push_back(renderable);
}

void Renderer::NextObject()
{
	++currentlyRendered;

	if (currentlyRendered >= renderables.size())
		currentlyRendered = 0;
}

