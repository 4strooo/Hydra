#pragma once
#include <Math/vectors.h>
#include <string>

class Transform
{
public:
	Transform(unsigned int identifier);
	Vectors::Vector2 Up();
	Vectors::Vector2 Down();
	Vectors::Vector2 Left();
	Vectors::Vector2 Right();
	Vectors::Vector2 CenterPos();
	std::string tag;
	unsigned int ID;
	Vectors::Vector2 position;
	float rotation;
	Vectors::Vector2 scale;
};