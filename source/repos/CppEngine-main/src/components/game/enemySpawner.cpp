#include <components/game/enemySpawner.h>
#include <core/serviceHandler.h>
#include <components/game/enemyScript.h>
#include <components/spriteRenderer.h>
#include <systems/clock.h>
#include <random>
#include <cmath>


void EnemySpawner::Start(Transform* parent)
{
	transform = parent;
	entitySystem = ServiceHandler::instance->GetModule<EntitySystem>();
	clock = ServiceHandler::instance->GetModule<Clock>();
}

void EnemySpawner::Update()
{

}

void EnemySpawner::SetPlayer(Entity* playerObj)
{
	player = playerObj;
}

void EnemySpawner::SpawnEnemy()
{
	std::random_device seed;
	std::mt19937 mt(seed());
	std::uniform_real_distribution<double> xDistribution(minValues.x, maxValues.x);
	std::uniform_real_distribution<double> yDistribution(minValues.y, maxValues.y);
	
	Entity* enemy = entitySystem->CreateEntity();
	enemy->transform.scale = Vectors::Vector2(32.0f, 32.0f);
	enemy->AddComponent<SpriteRenderer>();
	enemy->GetComponent<SpriteRenderer>()->SetSprite("resources/enemyGlow.bmp");
	enemy->AddComponent<RectCollider>();
	enemy->AddComponent<EnemyScript>();
	enemy->GetComponent<EnemyScript>()->units = &enemies;
	enemy->GetComponent<EnemyScript>()->SetPlayer(player->transform.ID);
	enemy->GetComponent<EnemyScript>()->moveSpeed += speedBoost;
	enemy->transform.position = Vectors::Vector2(xDistribution(mt), yDistribution(mt));
	while (std::sqrtf(std::powf((player->transform.CenterPos().x - enemy->transform.CenterPos().x), 2.0f)
		+ std::powf((player->transform.CenterPos().y - enemy->transform.CenterPos().y), 2.0f)) < 320.0f)
	{
		enemy->transform.position = Vectors::Vector2(xDistribution(mt), yDistribution(mt));
	}
	enemies.push_back(&enemy->transform);

	std::uniform_real_distribution<double> timeDistribution(minSpawnTime, maxSpawnTime);
	std::function<void()> spawnFunc = [&] {SpawnEnemy(); };
	clock->StartTimer(spawnFunc, timeDistribution(mt));

	if (maxSpawnTime > minSpawnTime + 0.1f)
	{
		maxSpawnTime -= 0.1f;
	}
	if (speedBoost < 25.0f)
	{
		speedBoost += 0.1f;
	}
}