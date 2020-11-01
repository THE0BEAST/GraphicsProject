#pragma once

#include "math/Vector3.h"


class Light
{
public:
	Vector3 position = Vector3::Zero();
	Vector3 intensity = Vector3(1,1,1);
	Vector3 ambientIntensity = Vector3(0.3f, 0.3f, 0.3f);

	Light();
	Light(Vector3 position, Vector3 intensity, Vector3 ambientIntensity);
	void IncreaseIntensity(float ammount);
	void DecreaseIntensity(float ammount);
};