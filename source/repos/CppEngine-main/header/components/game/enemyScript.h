#pragma once
#include <core/component.h>
#include <systems/clock.h>
#include <components/rectCollider.h>
#include <Math/vectors.h>
#include <vector>

class EnemyScript : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	void SetPlayer(int playerID);
	void OnCollisionEnter();
	void OnCollisionExit();
	std::vector<Transform*>* units = nullptr;
	float moveSpeed = 150.0f;

private:
	Vectors::Vector2 Alignment();
	Vectors::Vector2 Cohesion();
	Vectors::Vector2 Separation();
	float Distance(Vectors::Vector2 first, Vectors::Vector2 second);
	Clock* clock = nullptr;
	RectCollider* collider = nullptr;
	Transform* transform = nullptr;
	Transform* playerTransform = nullptr;
};