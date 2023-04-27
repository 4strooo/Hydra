#pragma once
#include <core/component.h>
#include <systems/clock.h>
#include <vector>
#include <systems/entitySystem.h>

class EnemySpawner : public Component 
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	void SetPlayer(Entity* playerObj);
	void SpawnEnemy();
	std::vector<Transform*> enemies;
	
private:
	Transform* transform = nullptr;
	Clock* clock = nullptr;
	EntitySystem* entitySystem = nullptr;
	Entity* player = nullptr;
	Vectors::Vector2 minValues = Vectors::Vector2(-100.0f, -100.0f);
	Vectors::Vector2 maxValues = Vectors::Vector2(1600.0f, 900.0f);
	float minSpawnTime = 0.5f;
	float maxSpawnTime = 5.0f;
	float speedBoost = 0.0f;
};