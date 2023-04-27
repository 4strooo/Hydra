#include <Math/collisionDetection.h>

bool Physics::OverlapRects(SDL_FRect first, SDL_FRect second)
{
	if (first.x + first.w > second.x && first.x < second.x + second.w)
	{
		if (first.y + first.h > second.y && first.y < second.y + second.h)
		{
			return true;
		}
	}
	return false;
}

bool Physics::OverlapSphere(Vectors::Vector2 firstCenter, Vectors::Vector2 secondCenter, float firstRadius, float secondRadius)
{
	if (abs((firstCenter - secondCenter).Magnitude()) < abs(firstRadius - secondRadius))
	{
		return true;
	}
	return false;
}