#pragma once

#include "math/Vector3.h"
#include "math/Matrix4x4.h"

class Camera
{
public:
	Vector3 position;
	Vector3 lookAt;
	Vector3 cameraUp;

	Camera();
	Camera(Vector3 position, Vector3 lookAt, Vector3 cameraUp);
	~Camera();

	Matrix4x4 GetViewMatrix();
};

