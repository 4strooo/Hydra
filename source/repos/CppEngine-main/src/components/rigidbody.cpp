#include <components/rigidbody.h>
#include <core/serviceHandler.h>

void Rigidbody::Start(Transform* parent)
{
	transform = parent;
	clock = ServiceHandler::instance->GetModule<Clock>();
}

void Rigidbody::Update()
{
	transform->position += velocity;
	velocity -= velocity * friction * clock->GetDeltaTime();
	velocity.ClampMagnitude(maxSpeed);
}

void Rigidbody::AddForce(Vectors::Vector2 vector)
{
	velocity += vector / mass;
}