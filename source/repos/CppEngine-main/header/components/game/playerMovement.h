#pragma once
#include <core/component.h>
#include <systems/inputHandler.h>
#include <systems/clock.h>
#include <components/rigidbody.h>
#include <systems/entitySystem.h>
#include <systems/camera.h>
#include <components/rectCollider.h>

class PlayerMovement : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	void OnCollisionEnter();
	void OnCollisionExit();
	void StopDash();
	void AllowDash();
	void ClampMovement();

private:
	Transform* transform = nullptr;
	InputHandler* inputManager = nullptr;
	EntitySystem* entityManager = nullptr;
	Clock* clock = nullptr;
	Camera* cam = nullptr;
	RectCollider* collider;
	float speed = 200.0f;

	float dashMultiplier = 6.0f;
	bool isDashing = false;
	bool canDash = true;
};