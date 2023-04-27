#pragma once
#include <core/component.h>
#include <systems/clock.h>
#include <components/rectCollider.h>
#include <Math/vectors.h>

class BulletMovement : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	bool Returning();
	void OnColEnter();
	void OnColExit();

private:
	void SelfDestruct();
	Transform* transform = nullptr;
	Clock* clock = nullptr;
	RectCollider* collider;
	float moveSpeed = 500.0f;
	bool isReturning = false;
	Vectors::Vector2 velocity;
};