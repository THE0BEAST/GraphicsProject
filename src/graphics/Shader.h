#pragma once

#include <vector>
#include <GL/glew.h>

#include "math/Matrix4x4.h"
#include "graphics/Texture.h"
#include "other/Light.h"
#include "graphics/Material.h"
#include "Utils/FileReaders.h"

class Shader
{
private:
public:
	GLuint program;
	Shader(const char* vertexPath, const char* fragPath);
	~Shader();

	void Enable();
	void Disable();

	void AttachTexture(Texture &texture);
	void AttachUniform1f(const GLchar* name, const float &data);
	void AttachUniform3f(const GLchar* name, const Vector3 &data);
	void AttachUniformMatrix4f(const GLchar* name, const Matrix4x4 &data);
	void AttachUniformLight(const Light *data);
	void AttachUniformMaterial(const Material *data);
};