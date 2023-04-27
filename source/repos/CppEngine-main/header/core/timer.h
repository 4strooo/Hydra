#pragma once
#include <functional>

class Timer
{
public:
	Timer(std::function<void()> function, float time);
	std::function<void()> func;
	float duration;
};