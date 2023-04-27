#include <components/game/scoreManager.h>
#include <core/serviceHandler.h>
#include <components/spriteRenderer.h>
#include <cmath>
#include <random>

void ScoreManager::Start(Transform* parent)
{
	entityManager = ServiceHandler::instance->GetModule<EntitySystem>();

	for (int i = 0; i < 4; i++)
	{
		Entity* letter = entityManager->CreateEntity();
		letter->transform.scale = Vectors::Vector2(20.0f, 32.0f);
		letter->AddComponent<SpriteRenderer>();
		letter->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/numbers.bmp", Vectors::Vector2(0.0, 0.0f), 20);
		letter->transform.position = Vectors::Vector2(700.0f + (20 * i), 20.0f);
		textLetters.push_back(letter);
	}
	std::reverse(textLetters.begin(), textLetters.end());
	objectList = *entityManager->GetAllEntities();
}

void ScoreManager::Update()
{
	std::vector<Entity*> oldList = objectList;
	int oldAmount = 0;
	for (int i = 0; i < oldList.size(); i++)
	{
		if (oldList[i] != nullptr)
		{
			oldAmount += 1;
		}
	}

	objectList = *entityManager->GetAllEntities();
	int amount = 0;
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] != nullptr)
		{
			amount += 1;
		}
	}


	if (oldAmount > amount)
	{
		std::random_device seed;
		std::mt19937 mt(seed());
		std::uniform_real_distribution<double> distribution(3, 12);
		AddScore((int)distribution(mt));
	}

	for (int i = 0; i < textLetters.size(); i++)
	{
		int digit = 0;
		if (i > 0) 
		{
			digit = (score / (int)std::pow(10.0, i)) % 10;
		}
		else 
		{
			digit = score % 10;
		}
		textLetters[i]->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/numbers.bmp", Vectors::Vector2(digit, 0.0f), 20);
		textLetters[i]->transform.position = Vectors::Vector2(775.0f - (20 * i), 20.0f) + ServiceHandler::instance->GetModule<Camera>()->offset;
	}
}

int ScoreManager::GetScore()
{
	return score;
}

void ScoreManager::AddScore(int amount)
{
	if (score < 9999) 
	{
		score += amount;
	}
}