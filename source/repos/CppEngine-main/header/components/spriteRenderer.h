#pragma once
#include <core/component.h>
#include <systems/renderSystem.h>
#include <core/sprite.h>
#include <systems/assetManager.h>

class SpriteRenderer : public Component
{
public:
	void Start(Transform* parent) override;
	void SetSprite(std::string path);
	void SetSpriteSheet(std::string path, Vectors::Vector2 offset, int tileSize);
	void Update() override;
	~SpriteRenderer() override;
private:
	Transform* transform = nullptr;
	Sprite* sprite = nullptr;
	RenderSystem* renderModule = nullptr;
	AssetManager* assetModule = nullptr;
};