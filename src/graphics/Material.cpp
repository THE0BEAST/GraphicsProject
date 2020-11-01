#include "Material.h"

Material::Material()
{
}

Material::Material(const char* fileName)
{
	this->texture = Texture(fileName);
}

Material::Material(const char* fileName, Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, float shininess)
{
	this->texture = Texture(fileName);
	this->ambientReflection = ambientReflection;
	this->diffuseReflection = diffuseReflection;
	this->specularReflection = specularReflection;
	this->shininess = shininess;
}
