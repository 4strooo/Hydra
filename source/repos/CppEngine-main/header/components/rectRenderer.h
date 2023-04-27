#pragma once
#include <core/component.h>
#include <SDL.h>
#include <systems/renderSystem.h>

class RectRenderer : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;

private:
	Transform* transform = nullptr;
	SDL_FRect rect = SDL_FRect();
	RenderSystem* renderModule = nullptr;
};