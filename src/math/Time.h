#pragma once

#include <chrono>

class Time
{
private:
	static float deltaTime;
	static float frameRate;

public:
	static const float DeltaTime();
	static const float FrameRate();
	static void UpdateDeltaTime();
};