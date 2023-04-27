#pragma once
#include <vector>
#include <Math/vectors.h>
#include <core/component.h>
#include <core/transform.h>

class Entity 
{
public:
	Transform transform = Transform(ID);
	~Entity();
	void Start(unsigned int identifier); // Entities take in an ID in their start functions, hence why all entity creation must be done through EntitySystem's interface
	void Update(); // Update runs every frame
	template <typename Comp>
	void AddComponent()
	{
		Comp* comp = new Comp(); // Handled
		if (dynamic_cast<Component*>(comp) != nullptr) // If a non-component type is passed in, the addition gets cancelled and the heap memory freed
		{
			components.push_back(comp);
			comp->Start(&transform); // Transform date is passed to all components
		}
		else
		{
			delete comp;
		}
	}

	template <typename Comp>
	Comp* GetComponent() // Gets a component of the template type
	{
		for (int i = 0; i < components.size(); i++)
		{
			Comp* component = dynamic_cast<Comp*>(components[i]);
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr; // Returns null if no component has been found
	}

	template <typename Comp>
	void RemoveComponent()
	{
		for (int i = 0; i < components.size(); i++) 
		{
			Comp* component = dynamic_cast<Comp*>(components[i]);
			if (component != nullptr)
			{
				components.erase(components.begin() + i);
				delete component;
			}
		}
	}

private:
	std::vector<Component*> components = std::vector<Component*>();
	unsigned int ID = 0;
};