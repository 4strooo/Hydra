#pragma once
#include <Math/vectors.h>
#include <SDL.h>

namespace Physics
{
	bool OverlapRects(SDL_FRect first, SDL_FRect second);
	bool OverlapSphere(Vectors::Vector2 firstCenter, Vectors::Vector2 secondCenter, float firstRadius, float secondRadius);
}