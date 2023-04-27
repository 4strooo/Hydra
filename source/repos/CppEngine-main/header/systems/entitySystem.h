#pragma once
#include <core/subsystem.h>
#include <core/entity.h>
#include <core/serviceHandler.h>
class EntitySystem : public SubSystem
{
public:
	Entity* CreateEntity();
	Entity* GetEntity(unsigned int ID);
	std::vector<Entity*>* GetAllEntities();
	void UpdateEntities();
	void DestroyEntity(unsigned int ID);
private:
	std::vector<Entity*> entityList;
	unsigned int nextID = 1;
};