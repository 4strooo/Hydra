#include <components/game/enemyScript.h>
#include <core/serviceHandler.h>
#include <systems/entitySystem.h>
#include <cmath>

#define PI 3.14159265358979323846f

void EnemyScript::Start(Transform* parent)
{
	transform = parent;
	clock = ServiceHandler::instance->GetModule<Clock>();
	collider = ServiceHandler::instance->GetModule<EntitySystem>()->GetEntity(transform->ID)->GetComponent<RectCollider>();
	std::function<void()> colEnter = [&] {OnCollisionEnter(); };
	std::function<void()> colExit = [&] {OnCollisionExit(); };
	collider->AddListener(colEnter, colExit);
}

void EnemyScript::Update()
{
	if (playerTransform != nullptr) 
	{
		Vectors::Vector2 playerPos = playerTransform->CenterPos();
		Vectors::Vector2 direction = playerPos - transform->CenterPos();
		direction.Normalize();
		direction = direction + Alignment() + Cohesion() + Separation() * 1.3f;
		direction.Normalize();
		float euler = atan2(direction.y, direction.x);
		transform->rotation = (euler * 180.0f / PI) + 90.0f;
		transform->position += direction * moveSpeed * clock->GetDeltaTime();
	}
}

void EnemyScript::SetPlayer(int playerID)
{
	playerTransform = &ServiceHandler::instance->GetModule<EntitySystem>()->GetEntity(playerID)->transform;
}

void EnemyScript::OnCollisionEnter()
{
	if (collider->col->tag == "Boomerang")
	{
		// Add death animation here
		ServiceHandler::instance->GetModule<EntitySystem>()->DestroyEntity(transform->ID);
	}
	else if (collider->col->tag == "Player")
	{
		// GAME OVER
		for (int i = 0; i < units->size(); i++)
		{
			if ((*units)[i]->ID == transform->ID)
			{
				units->erase(units->begin() + i);
			}
		}
		ServiceHandler::instance->GetModule<EntitySystem>()->DestroyEntity(playerTransform->ID);
		ServiceHandler::instance->isRunning = false;
	}
}

void EnemyScript::OnCollisionExit()
{

}

Vectors::Vector2 EnemyScript::Alignment()
{
	Vectors::Vector2 dir = Vectors::Vector2(0.0f, 0.0f);
	int neighbours = 0;
	for (int i = 0; i < units->size(); i++)
	{
		if ((*units)[i]->ID != transform->ID && Distance(transform->CenterPos(), (*units)[i]->CenterPos()) < 128.0f)
		{
			dir += (*units)[i]->Up();
			neighbours++;
		}
	}
	if (neighbours < 1)
	{
		return Vectors::Vector2(0.0f, 0.0f);
	}
	dir /= neighbours;
	dir.Normalize();
	return dir;
}

Vectors::Vector2 EnemyScript::Cohesion()
{
	Vectors::Vector2 dir = Vectors::Vector2(0.0f, 0.0f);
	int neighbours = 0;
	for (int i = 0; i < units->size(); i++)
	{
		if ((*units)[i]->ID != transform->ID && Distance(transform->CenterPos(), (*units)[i]->CenterPos()) < 128.0f)
		{
			dir += (*units)[i]->CenterPos();
			neighbours++;
		}
	}
	if (neighbours < 1)
	{
		return Vectors::Vector2(0.0f, 0.0f);
	}
	dir /= neighbours;
	dir -= transform->CenterPos();
	dir.Normalize();
	return dir;
}

Vectors::Vector2 EnemyScript::Separation()
{
	Vectors::Vector2 dir = Vectors::Vector2(0.0f, 0.0f);
	int neighbours = 0;
	for (int i = 0; i < units->size(); i++)
	{
		if ((*units)[i]->ID != transform->ID && Distance(transform->CenterPos(), (*units)[i]->CenterPos()) < 128.0f)
		{
			dir += (*units)[i]->CenterPos() - transform->CenterPos();
			neighbours++;
		}
	}
	if (neighbours < 1)
	{
		return Vectors::Vector2(0.0f, 0.0f);
	}
	dir /= neighbours;
	dir *= -1.0f;
	dir.Normalize();
	return dir;
}

float EnemyScript::Distance(Vectors::Vector2 first, Vectors::Vector2 second)
{
	return std::sqrtf(std::powf((second.x - first.x), 2.0f) + std::powf((second.y - first.y), 2.0f));
}