#include "Light.h"

Light::Light()
{}

Light::Light(Vector3 position, Vector3 intensity, Vector3 ambientIntensity) : position(position), intensity(intensity), ambientIntensity(ambientIntensity)
{}

void Light::IncreaseIntensity(float ammount)
{
	intensity += Vector3(ammount, ammount, ammount);
	if (intensity.x > 1)
		intensity = Vector3(1, 1, 1);
}

void Light::DecreaseIntensity(float ammount)
{
	intensity -= Vector3(ammount, ammount, ammount);
	if (intensity.x < 0)
		intensity = Vector3(0, 0, 0);
}