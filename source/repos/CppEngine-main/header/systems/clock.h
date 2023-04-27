#pragma once
#include <SDL.h>
#include <core/subsystem.h>
#include <functional>
#include <core/timer.h>

class Clock : public SubSystem
{
public:
	Clock();
	void Tick();
	float GetDeltaTime();
	void StartTimer(std::function<void()> func, float time); // TODO: Allow this to take in a raw function pointer or lambda

private:
	std::vector<Timer> timers;
	std::vector<float> timerDurations;
	unsigned int deltaTime;
	unsigned int lastTime;
};