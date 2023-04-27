#pragma once
#include <core/component.h>
#include <Math/vectors.h>
#include <systems/clock.h>

class Rigidbody : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	void AddForce(Vectors::Vector2 vector);
	Vectors::Vector2 velocity;
	float friction = 0.3f;
private:
	Clock* clock = nullptr;
	float mass = 100.0f;
	float maxSpeed = 20.0f;
	Transform* transform = nullptr;
};