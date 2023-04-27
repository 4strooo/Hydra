#pragma once
#include <core/component.h>
#include <vector>
#include <SDL.h>
#include <functional>

class RectCollider : public Component
{
public:
	Transform* transform;
	Transform* col;
	void Start(Transform* parent) override;
	void Update() override;
	~RectCollider() override;
	void AddListener(std::function<void()> enterFunc, std::function<void()> exitFunc);
	void OnCollisionEnter(Transform* other);
	void OnCollisionExit(Transform* other);
	Vectors::Vector2 GetCollisionDir(Transform* second); // DOES NOT WORK WITH DIAGONAL COLLISIONS
	SDL_FRect GetRect();

private:
	SDL_FRect rect;
	std::vector<std::function<void()>> enterListeners;
	std::vector<std::function<void()>> exitListeners;
	std::vector<int> collided;
};