#include <core/timer.h>

Timer::Timer(std::function<void()> function, float time)
{
	func = function;
	duration = time;
}