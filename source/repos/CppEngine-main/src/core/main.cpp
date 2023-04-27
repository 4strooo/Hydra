#include <SDL.h>
#include <iostream>
#include <core/game.h>
#include <components/rectRenderer.h>
#include <components/game/playerMovement.h>
#include <components/game/playerShooting.h>
#include <components/game/enemyScript.h>
#include <components/game/enemySpawner.h>
#include <components/game/scoreManager.h>
#include <systems/assetManager.h>
#include <components/spriteRenderer.h>
#include <components/rectCollider.h>

using namespace Vectors;

int main(int argc, char** argv)
{
	Game game = Game();
	EntitySystem* entitySystem = ServiceHandler::instance->GetModule<EntitySystem>();
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);

	Entity* player = entitySystem->CreateEntity();
	player->transform.position = Vector2(display.w / 2, display.h / 2);
	player->transform.scale = Vector2(32.0f, 32.0f);
	player->AddComponent<SpriteRenderer>();
	player->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/player.bmp", Vector2(0.0f, 0.0f), 32);
	player->AddComponent<RectCollider>();
	player->AddComponent<PlayerMovement>();
	player->AddComponent<PlayerShooting>();

	Entity* ceiling = entitySystem->CreateEntity();
	ceiling->AddComponent<RectRenderer>();
	ceiling->AddComponent<RectCollider>();
	ceiling->transform.position = Vector2(0.0f, 0.0f);
	ceiling->transform.scale = Vector2(1537.0f, 16.0f);
	ceiling->transform.tag = "Wall";

	Entity* leftWall = entitySystem->CreateEntity();
	leftWall->AddComponent<RectRenderer>();
	leftWall->AddComponent<RectCollider>();
	leftWall->transform.position = Vector2(0.0f, 0.0f);
	leftWall->transform.scale = Vector2(16.0f, 842.0f);
	leftWall->transform.tag = "Wall";

	Entity* floor = entitySystem->CreateEntity();
	floor->AddComponent<RectRenderer>();
	floor->AddComponent<RectCollider>();
	floor->transform.position = Vector2(0.0f, 826.0f);
	floor->transform.scale = Vector2(1537.0f, 16.0f);
	floor->transform.tag = "Wall";

	Entity* rightWall = entitySystem->CreateEntity();
	rightWall->AddComponent<RectRenderer>();
	rightWall->AddComponent<RectCollider>();
	rightWall->transform.position = Vector2(1521.0f, 0.0f);
	rightWall->transform.scale = Vector2(16.0f, 842.0f);
	rightWall->transform.tag = "Wall";

	Entity* enemySpawner = entitySystem->CreateEntity();
	enemySpawner->AddComponent<EnemySpawner>();
	enemySpawner->GetComponent<EnemySpawner>()->SetPlayer(player);
	enemySpawner->GetComponent<EnemySpawner>()->SpawnEnemy();


	Entity* scoreManager = entitySystem->CreateEntity();
	scoreManager->AddComponent<ScoreManager>();


	while (ServiceHandler::instance->isRunning)
	{
		game.Update();
	}
	std::cout << "Score: " << scoreManager->GetComponent<ScoreManager>()->GetScore() << '\n';
	game.Cleanup();
	SDL_Quit();
	std::cin.get();
	return 0;
}