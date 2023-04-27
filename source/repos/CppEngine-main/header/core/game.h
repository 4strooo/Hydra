#pragma once
#include <SDL.h>
#include <systems/inputHandler.h>
#include <systems/entitySystem.h>
#include <systems/renderSystem.h>
#include <systems/clock.h>
#include <systems/assetManager.h>
#include <systems/collisionSystem.h>
#include <systems/camera.h>
#include <core/serviceHandler.h>

class Game
{
public:
	Game();
	void Update();
	void Cleanup();
	ServiceHandler* serviceManager;

private:
	SDL_Window* window;
	InputHandler* inputManager; // TODO: There is no need to have a variable for each system, they can simply implement a shared interface
	EntitySystem* entityManager;
	RenderSystem* renderManager;
	Clock* clock;
	AssetManager* assetManager;
	CollisionSystem* colDetection;
	Camera* mainCam;
};