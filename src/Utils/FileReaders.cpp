#include "FileReaders.h"

unsigned char* LoadBMP(const char *filename, unsigned int &width, unsigned int &height)
{
	unsigned char* pixels;
	FILE* file;
	fopen_s(&file, filename, "rb");

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, file); // read the 54-byte header

	// extract image height and width from header
	width = *(unsigned int*)&info[18];
	height = *(unsigned int*)&info[22];

	int size = 3 * width * height; // calculate the size of pixel data
	pixels = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(pixels, sizeof(unsigned char), size, file); // read the rest of the data at once
	fclose(file);

	for (int i = 0; i < size; i += 3)
	{
		unsigned char tmp = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = tmp;
	}

	return pixels;
}

char* ReadShader(const char *filename)
{
	std::ifstream infile;
	infile.open(filename, std::ios::in);
	if (!infile) throw " Error opening shader source code";

	unsigned long lenght;
	if (!infile.good()) lenght = 0;
	infile.seekg(0, std::ios::end);
	lenght = infile.tellg();
	infile.seekg(std::ios::beg);

	char* ShaderSource = new char[lenght + 1];
	ShaderSource[lenght] = 0;
	unsigned int i = 0;
	while (infile.good()) 
	{
		ShaderSource[i] = infile.get();
		if (!infile.eof()) i++;
	}
	ShaderSource[i] = 0;
	infile.close();
	return ShaderSource;
}

bool loadOBJ(const char *path, std::vector<Vector3> &out_vertices, std::vector<Vector2> &out_uvs, std::vector<Vector3> &out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vector3> temp_vertices;
	std::vector<Vector2> temp_uvs;
	std::vector<Vector3> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) 
	{
		printf("Failed to open file \n");
		getchar();
		return false;
	}

	while (true) 
	{
		char lineHeader[128];
		
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0) 
		{
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) 
		{
			Vector2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) 
		{
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) 
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) 
			{
				printf("File can't be read! \n");
				fclose(file);
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else 
		{
			// Consume unneeded lines
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) 
	{
		// Get the vertices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		Vector3 vertex = temp_vertices[vertexIndex - 1];
		Vector2 uv = temp_uvs[uvIndex - 1];
		Vector3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}
	fclose(file);
	return true;
}