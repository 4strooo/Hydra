#include <core/game.h>
#include <components/rectRenderer.h>

Game::Game()
{
	window = SDL_CreateWindow("Shmup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 550, 750, SDL_WINDOW_MAXIMIZED); // TODO: Make game fullscreen?
	serviceManager = new ServiceHandler();
	inputManager = serviceManager->AddModule<InputHandler>();
	entityManager = serviceManager->AddModule<EntitySystem>();
	mainCam = serviceManager->AddModule<Camera>();
	renderManager = serviceManager->AddModule<RenderSystem>();
	clock = serviceManager->AddModule<Clock>();
	assetManager = serviceManager->AddModule<AssetManager>();
	colDetection = serviceManager->AddModule<CollisionSystem>();
}

void Game::Update() // All these functions could be turned into an update interface for each subsystem
{
	clock->Tick();
	inputManager->CheckEvent();
	colDetection->CheckCollisions();
	entityManager->UpdateEntities();
	renderManager->Render();
}

void Game::Cleanup() // Temporary
{
	delete inputManager;
	delete entityManager;
	delete renderManager;
	delete clock;
	delete assetManager;
	delete colDetection;
	delete mainCam;
}