#pragma once
#include <vector>
#include <core/subsystem.h>

class ServiceHandler
{
public:
	static ServiceHandler* instance; // A singleton is unavoidable here unless I want to pass the service handler to every single class
	bool isRunning;
	ServiceHandler();

	template <typename System>
	System* GetModule() // All references to engine subsystems within components should be received from this function
	{
		for (int i = 0; i < systems.size(); i++)
		{
			System* subsystem = dynamic_cast<System*>(systems[i]);
			if (subsystem != nullptr)
			{
				return subsystem;
			}
		}
		return nullptr;
	}

	template <typename System>
	System* AddModule() // To only be called by the game class.
	{
		System* sys = new System();
		if (dynamic_cast<SubSystem*>(sys) != nullptr)
		{
			systems.push_back(sys);
			return sys;
		}
		delete sys;
		return nullptr;
	}

private:
	std::vector<SubSystem*> systems;
};