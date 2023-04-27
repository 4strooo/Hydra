#include <components/game/bulletMovement.h>
#include <core/serviceHandler.h>
#include <systems/entitySystem.h>
#include <components/spriteRenderer.h>
#include <iostream>

void BulletMovement::Start(Transform* parent)
{
	transform = parent;
	clock = ServiceHandler::instance->GetModule<Clock>();
	collider = ServiceHandler::instance->GetModule<EntitySystem>()->GetEntity(transform->ID)->GetComponent<RectCollider>();
	std::function<void()> collEnter = [&] {OnColEnter(); };
	std::function<void()> collExit = [&] {OnColExit(); };
	collider->AddListener(collEnter, collExit);
	isReturning = false;
	transform->tag = "Boomerang";
	velocity = transform->Up();
}

void BulletMovement::Update()
{
	transform->position += velocity * moveSpeed * clock->GetDeltaTime();
	transform->rotation += velocity.x * moveSpeed * clock->GetDeltaTime();
	if (transform->position.x < 16.0f)
	{
		transform->position.x = 15.0f;
		velocity.x = -velocity.x;
	}
	if (transform->position.x > 1521.0f - transform->scale.x)
	{
		transform->position.x = 1522.0f - transform->scale.x;
		velocity.x = -velocity.x;
	}
	if (transform->position.y < 16.0f)
	{
		transform->position.y = 15.0f;
		velocity.y = -velocity.y;
	}
	if (transform->position.y > 826.0f - transform->scale.y)
	{
		transform->position.y = 827.0f - transform->scale.y;
		velocity.y = -velocity.y;
	}
}

void BulletMovement::SelfDestruct()
{
	ServiceHandler::instance->GetModule<EntitySystem>()->DestroyEntity(transform->ID);
}

bool BulletMovement::Returning()
{
	return isReturning;
}

void BulletMovement::OnColEnter()
{
	if (collider->col->tag == "Wall")
	{
		isReturning = true;
		ServiceHandler::instance->GetModule<EntitySystem>()->GetEntity(transform->ID)->GetComponent<SpriteRenderer>()->SetSpriteSheet("resources/buzzsaw.bmp", Vectors::Vector2(0.0f, 0.0f), 64);
	}
	else if (collider->col->tag == "Player")
	{
		if (isReturning)
		{
			SelfDestruct();
		}
	}
}

void BulletMovement::OnColExit()
{

}