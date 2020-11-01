#include "Time.h"

using namespace std::chrono;

float Time::deltaTime;
float Time::frameRate;

const float Time::DeltaTime()
{
	return deltaTime;
}

const float Time::FrameRate()
{
	return frameRate;
}

void Time::UpdateDeltaTime()
{
	static milliseconds msTime = duration_cast<milliseconds> (system_clock::now().time_since_epoch());
	milliseconds msNewTime = duration_cast<milliseconds> (system_clock::now().time_since_epoch());
	deltaTime = (msNewTime - msTime).count() / 1000.0f; // deltaTime is used to keep movement constant across diffrent framerates
	msTime = msNewTime;
	

	static float passedTime;
	passedTime += deltaTime;
	if (passedTime > 0.5f)
	{
		frameRate = 1.0f / deltaTime;
		passedTime = 0;
	}
}