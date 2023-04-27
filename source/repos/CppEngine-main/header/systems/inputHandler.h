#pragma once
#include <core/subsystem.h>
#include <Math/vectors.h>
class InputHandler : public SubSystem
{
public:
	void CheckEvent();
	void PushEvent(int eventValue);
	void PopEvent(int eventValue);
	bool GetKey(int key);
	Vectors::Vector2 GetMouse();
	bool MouseDown();
	bool RightMouseDown();
private:
	std::vector<int> keys;
	bool mousePressed;
	bool rightMousePressed;
};