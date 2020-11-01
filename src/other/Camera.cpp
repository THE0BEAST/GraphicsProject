#include "Camera.h"

Camera::Camera() : position(Vector3::Zero())
{}

Camera::Camera(Vector3 position, Vector3 lookAt, Vector3 cameraUp) : position(position), lookAt(lookAt), cameraUp(cameraUp)
{}

Camera::~Camera()
{}

Matrix4x4 Camera::GetViewMatrix()
{
	return Matrix4x4::LookAt
	(
		position, // Camera position
		lookAt, // Look at
		Vector3::Up()  // Up direction
	);
}