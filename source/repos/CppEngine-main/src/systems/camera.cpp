#include <systems/camera.h>

Camera::Camera()
{
	screenRes = SDL_DisplayMode();
	SDL_GetCurrentDisplayMode(0, &screenRes);
}

void Camera::MoveTo(Vectors::Vector2 pos)
{
	offset = pos - Vectors::Vector2(screenRes.w / 2.0f, screenRes.h / 2.0f);
}