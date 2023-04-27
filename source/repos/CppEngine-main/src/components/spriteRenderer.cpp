#include <components/spriteRenderer.h>
#include <core/serviceHandler.h>
#include <systems/assetManager.h>
#include <iostream>

void SpriteRenderer::Start(Transform* parent)
{
	transform = parent;
	renderModule = ServiceHandler::instance->GetModule<RenderSystem>();
	assetModule = ServiceHandler::instance->GetModule<AssetManager>();
	sprite = new Sprite();
	sprite->sourceRect = SDL_Rect();
	sprite->rect = SDL_FRect();
	sprite->rotation = transform->rotation;
	renderModule->AddRenderable(sprite);

}

void SpriteRenderer::SetSprite(std::string path)
{
	sprite->texture = assetModule->LoadTexture(path);
	sprite->sourceRect.x = 0;
	sprite->sourceRect.y = 0;
	sprite->sourceRect.w = transform->scale.x;
	sprite->sourceRect.h = transform->scale.y;
}

void SpriteRenderer::SetSpriteSheet(std::string path, Vectors::Vector2 offset, int tileSize)
{
	sprite->texture = assetModule->LoadTexture(path);
	sprite->sourceRect.x = offset.x * tileSize;
	sprite->sourceRect.y = offset.y * tileSize;
	sprite->sourceRect.w = transform->scale.x;
	sprite->sourceRect.h = transform->scale.y;
}

void SpriteRenderer::Update()
{
	sprite->rotation = transform->rotation;
	sprite->rect.x = transform->position.x;
	sprite->rect.y = transform->position.y;
	sprite->rect.w = transform->scale.x;
	sprite->rect.h = transform->scale.y;
}

SpriteRenderer::~SpriteRenderer()
{
	assetModule->Dereference(sprite->texture);
	renderModule->RemoveRenderable(sprite);
	delete sprite;
}