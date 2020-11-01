#include "Shader.h"


Shader::Shader(const char * vertexPath, const char * fragPath)
{
	program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertSource = ReadShader(vertexPath);
	const char* fragSource = ReadShader(fragPath);

	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint lenght;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &lenght);

		if (lenght > 0)
		{
			char *log = (char*)malloc(lenght);
			GLsizei written;
			glGetShaderInfoLog(vertex, lenght, &written, log);
			throw log;
		}
	}

	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint lenght;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &lenght);

		if (lenght > 0)
		{
			char *log = (char*)malloc(lenght);
			GLsizei written;
			glGetShaderInfoLog(fragment, lenght, &written, log);
			throw log;
		}
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glBindAttribLocation(program, 0, "in_position");
	glBindAttribLocation(program, 1, "in_normal"); 
	glBindAttribLocation(program, 2, "in_uv");

	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vertex);
	glDetachShader(program, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader() 
{
	glDeleteProgram(program);
}

void Shader::Enable()
{
	glUseProgram(program);
}

void Shader::Disable()
{
	glUseProgram(0);
}


void Shader::AttachTexture(Texture &texture)
{
	GLuint TextureID = glGetUniformLocation(program, "textureSampler");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glUniform1i(TextureID, 0);
}

void Shader::AttachUniform1f(const GLchar *name, const float &data)
{
	GLuint ID = glGetUniformLocation(program, name);
	glUniform1f(ID, data);
}

void Shader::AttachUniform3f(const GLchar *name, const Vector3 &data)
{
	GLuint ID = glGetUniformLocation(program, name);
	glUniform3f(ID, data.x, data.y, data.z);
}

void Shader::AttachUniformMatrix4f(const GLchar *name, const Matrix4x4 &data)
{
	GLuint ID = glGetUniformLocation(program, name);
	glUniformMatrix4fv(ID, 1, GL_FALSE, data.elements);
}

void Shader::AttachUniformLight(const Light *data)
{
	GLuint ID = glGetUniformLocation(program, "light.position");
	glUniform4f(ID, data->position.x, data->position.y, data->position.z, 1.0f);

	ID = glGetUniformLocation(program, "light.intensity");
	glUniform3f(ID, data->intensity.x, data->intensity.y, data->intensity.z);

	ID = glGetUniformLocation(program, "light.ambientIntensity");
	glUniform3f(ID, data->ambientIntensity.x, data->ambientIntensity.y, data->ambientIntensity.z);
}

void Shader::AttachUniformMaterial(const Material *data)
{
	GLuint ID = glGetUniformLocation(program, "material.texture");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->texture.texture);
	glUniform1i(ID, 0);

	ID = glGetUniformLocation(program, "material.ambientReflection");
	glUniform4f(ID, data->ambientReflection.x, data->ambientReflection.y, data->ambientReflection.z, 1.0f);

	ID = glGetUniformLocation(program, "material.diffuseReflection");
	glUniform3f(ID, data->diffuseReflection.x, data->diffuseReflection.y, data->diffuseReflection.z);

	ID = glGetUniformLocation(program, "material.specularReflection");
	glUniform3f(ID, data->specularReflection.x, data->specularReflection.y, data->specularReflection.z);

	ID = glGetUniformLocation(program, "material.shininess");
	glUniform1f(ID, data->shininess);
}