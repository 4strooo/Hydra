#pragma once
#include <core/component.h>
#include <systems/inputHandler.h>
#include <systems/entitySystem.h>

class PlayerShooting : public Component
{
public:
	void Start(Transform* parent) override;
	void Update() override;
	void Reload();
private:
	void Shoot();
	Transform* transform = nullptr;
	InputHandler* input = nullptr;
	EntitySystem* entityManager = nullptr;
	float shootInterval = 1.0f;
	bool canShoot = false;
};