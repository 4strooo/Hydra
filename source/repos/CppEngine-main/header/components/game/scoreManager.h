#pragma once
#include <core/component.h>
#include <systems/entitySystem.h>

class ScoreManager : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	int GetScore();
	void AddScore(int amount);

private:
	int score = 0000;
	EntitySystem* entityManager;
	std::vector<Entity*> objectList;
	std::vector<Entity*> textLetters;
};