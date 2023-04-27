#pragma once
#include <core/subsystem.h>
#include <Math/vectors.h>
#include <SDL.h>

class Camera : public SubSystem
{
public:
	Camera();
	Vectors::Vector2 offset;
	void MoveTo(Vectors::Vector2 pos);
	
private:
	SDL_DisplayMode screenRes;
};