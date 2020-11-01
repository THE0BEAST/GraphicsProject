#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "math\Vector3.h"
#include "math\Vector2.h"

unsigned char* LoadBMP(const char *filename, unsigned int &width, unsigned int &height);
char* ReadShader(const char *filename);
bool loadOBJ(const char * path, std::vector<Vector3> &out_vertices, std::vector<Vector2> &out_uvs, std::vector<Vector3> &out_normals);