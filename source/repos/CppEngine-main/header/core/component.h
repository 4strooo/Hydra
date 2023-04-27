#pragma once
#include <core/transform.h>
class Component // Important note: Component is an abstract class, all custom components have to inherit from it
{
public:
	virtual void Start(Transform* parent) = 0;
	virtual void Update() = 0;
	virtual ~Component() = 0;
};