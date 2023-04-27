#include <components/game/playerMovement.h>
#include <core/serviceHandler.h>
#include <systems/entitySystem.h>
#include <components/game/bulletMovement.h>
#include <components/game/playerShooting.h>
#include <components/spriteRenderer.h>
#include <cmath>
#define PI 3.14159265358979323846f

void PlayerMovement::Start(Transform* parent)
{
	transform = parent;
	transform->tag = "Player";
	clock = ServiceHandler::instance->GetModule<Clock>();
	inputManager = ServiceHandler::instance->GetModule<InputHandler>();
	entityManager = ServiceHandler::instance->GetModule<EntitySystem>();
	cam = ServiceHandler::instance->GetModule<Camera>();
	collider = entityManager->GetEntity(transform->ID)->GetComponent<RectCollider>();
	std::function<void()> colEnter = [&] {OnCollisionEnter(); };
	std::function<void()> colExit = [&] {OnCollisionExit(); };
	collider->AddListener(colEnter, colExit);
}

void PlayerMovement::Update()
{
	cam->MoveTo(transform->CenterPos());
	if (!isDashing) 
	{
		float horizontalAxis = inputManager->GetKey(SDLK_d) - inputManager->GetKey(SDLK_a);
		float verticalAxis = inputManager->GetKey(SDLK_s) - inputManager->GetKey(SDLK_w);
		Vectors::Vector2 direction = Vectors::Vector2(horizontalAxis, verticalAxis);
		direction.ClampMagnitude(1.0f);
		transform->position += direction * speed * clock->GetDeltaTime();
		Vectors::Vector2 mousePos = inputManager->GetMouse() + cam->offset;
		float euler = atan2(mousePos.y - transform->CenterPos().y, mousePos.x - transform->CenterPos().x);
		transform->rotation = (euler * 180.0f / PI) + 90.0f;

		if (direction.x != 0.0f || direction.y != 0.0f)
		{
			entityManager->GetEntity(transform->ID)->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/player.bmp", Vectors::Vector2(1.0f, 0.0f), 32);
		}
		else 
		{
			entityManager->GetEntity(transform->ID)->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/player.bmp", Vectors::Vector2(0.0f, 0.0f), 32);
		}

		if (inputManager->RightMouseDown() && canDash)
		{
			canDash = false;
			isDashing = true;
			std::function<void()> dashFunc = [&] {StopDash(); };
			clock->StartTimer(dashFunc, 0.15f);
		}

	}
	else 
	{
		transform->position += transform->Up() * speed * dashMultiplier * clock->GetDeltaTime();
		entityManager->GetEntity(transform->ID)->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/player.bmp", Vectors::Vector2(2.0f, 0.0f), 32);
	}
	ClampMovement();
}

void PlayerMovement::OnCollisionEnter()
{	
	if (collider->col->tag == "Boomerang")
	{
		Entity* boomerang = ServiceHandler::instance->GetModule<EntitySystem>()->GetEntity(collider->col->ID);
		if (boomerang->GetComponent<BulletMovement>()->Returning())
		{
			ServiceHandler::instance->GetModule<EntitySystem>()->GetEntity(transform->ID)->GetComponent<PlayerShooting>()->Reload();
		}
	}
}

void PlayerMovement::OnCollisionExit()
{

}

void PlayerMovement::StopDash()
{
	isDashing = false;
	std::function<void()> allowDash = [&] {AllowDash(); };
	clock->StartTimer(allowDash, 1.0f);
}

void PlayerMovement::AllowDash()
{
	canDash = true;
}

void PlayerMovement::ClampMovement()
{
	if (transform->position.x < 16.0f)
	{
		transform->position.x = 16.0f;
	}
	if (transform->position.x > 1521.0f - transform->scale.x)
	{
		transform->position.x = 1521.0f - transform->scale.x;
	}
	if (transform->position.y < 16.0f)
	{
		transform->position.y = 16.0f;
	}
	if (transform->position.y > 826.0f - transform->scale.y)
	{
		transform->position.y = 826.0f - transform->scale.y;
	}
}