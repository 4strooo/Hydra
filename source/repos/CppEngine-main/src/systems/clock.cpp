#include <systems/clock.h>

Clock::Clock()
{
	lastTime = 0;
	deltaTime = 0;
}

void Clock::Tick()
{
	unsigned int currentTime = SDL_GetTicks();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	for (int i = timers.size() - 1; i >= 0; i--)
	{
		timerDurations[i] += deltaTime / 1000.0f;
		if (timerDurations[i] >= timers[i].duration)
		{
			timers[i].func();
			timers.erase(timers.begin() + i);
			timerDurations.erase(timerDurations.begin() + i);
		}
	}
}

float Clock::GetDeltaTime()
{
	return deltaTime / 1000.0f; // Raw delta time is in milliseconds, this converts it to seconds
}

void Clock::StartTimer(std::function<void()> func, float time)
{
	timers.push_back(Timer(func, time));
	timerDurations.push_back(0.0f);
}