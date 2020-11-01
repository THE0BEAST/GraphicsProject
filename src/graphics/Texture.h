#pragma once

#include <GL/glew.h>
#include "Utils/FileReaders.h"

class Texture
{
public:
	unsigned char* pixels; // Image pixels
	unsigned int width;
	unsigned int height;
	GLuint texture;
	
public:

	Texture();
	Texture(const char* fileName);
};

