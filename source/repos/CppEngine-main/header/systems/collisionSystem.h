#pragma once
#include <core/subsystem.h>
#include <SDL.h>
#include <components/rectCollider.h>
#include <vector>

class CollisionSystem : public SubSystem
{
public:
	void CheckCollisions();
	void CleanDead();
	bool isColliding(SDL_FRect first, SDL_FRect second);
	bool isDead(RectCollider* col);
	void AddCollider(RectCollider* collider);
	void RemoveCollider(RectCollider* collider);
private:
	std::vector<RectCollider*> colliders;
	std::vector<RectCollider*> deadColliders;
};