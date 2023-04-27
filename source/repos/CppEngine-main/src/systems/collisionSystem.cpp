#include <systems/collisionSystem.h>
#include <Math/collisionDetection.h>
#include <iostream>

void CollisionSystem::CheckCollisions()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		for (int j = 0; j < colliders.size(); j++)
		{
			if (i == j || isDead(colliders[j]))
			{
				continue;
			}
			if (isColliding(colliders[i]->GetRect(), colliders[j]->GetRect()))
			{
				colliders[i]->OnCollisionEnter(colliders[j]->transform);
			}
			else
			{
				colliders[i]->OnCollisionExit(colliders[j]->transform);
			}
		}
	}
	CleanDead();
}

void CollisionSystem::CleanDead()
{
	for (int i = colliders.size() - 1; i >= 0; i--)
	{
		if (isDead(colliders[i]))
		{
			colliders.erase(colliders.begin() + i);
		}
	}
	deadColliders.clear();
}

bool CollisionSystem::isDead(RectCollider* col)
{
	for (RectCollider* i : deadColliders)
	{
		if (i == col)
		{
			return true;
		}
	}
	return false;
}

bool CollisionSystem::isColliding(SDL_FRect first, SDL_FRect second)
{
	return Physics::OverlapRects(first, second);
}

void CollisionSystem::AddCollider(RectCollider* collider)
{
	colliders.push_back(collider);
}

void CollisionSystem::RemoveCollider(RectCollider* collider)
{
	deadColliders.push_back(collider);
}