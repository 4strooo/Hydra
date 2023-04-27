#include <components/game/playerShooting.h>
#include <core/serviceHandler.h>
#include <components/rectRenderer.h>
#include <components/spriteRenderer.h>
#include <Math/vectors.h>
#include <components/game/bulletMovement.h>
#include <components/rectCollider.h>
#include <systems/clock.h>

void PlayerShooting::Start(Transform* parent)
{
	transform = parent;
	input = ServiceHandler::instance->GetModule<InputHandler>();
	entityManager = ServiceHandler::instance->GetModule<EntitySystem>();
	canShoot = true;
}

void PlayerShooting::Update()
{
	if (input->MouseDown() && canShoot)
	{
		Shoot();
	}
}

void PlayerShooting::Shoot()
{
	
	Entity* bullet = entityManager->CreateEntity();
	bullet->transform.scale = Vectors::Vector2(64.0f, 64.0f);
	bullet->transform.position = transform->CenterPos() - Vectors::Vector2(32.0f, 0.0f);
	bullet->transform.rotation = transform->rotation;
	bullet->AddComponent<SpriteRenderer>();
	bullet->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/buzzsaw.bmp", Vectors::Vector2(1.0f, 0.0f), 64);
	bullet->AddComponent<RectCollider>();
	bullet->AddComponent<BulletMovement>();
	canShoot = false;
}

void PlayerShooting::Reload()
{
	canShoot = true;
}