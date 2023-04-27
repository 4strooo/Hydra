#include <systems/renderSystem.h>
#include <SDL.h>
#include <core/serviceHandler.h>

RenderSystem::RenderSystem()
{
	rects = std::vector<SDL_FRect*>();
	sprites = std::vector<Sprite*>();
	renderer = SDL_CreateRenderer(SDL_GetWindowFromID(1), 0, SDL_RENDERER_PRESENTVSYNC); // SDL Window IDs start at 1
	cam = ServiceHandler::instance->GetModule<Camera>();
}

void RenderSystem::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	RenderRects();
	RenderSprites();
	SDL_RenderPresent(renderer);
}

void RenderSystem::AddRenderable(SDL_FRect* rect)
{
	rects.push_back(rect);
}

void RenderSystem::AddRenderable(Sprite* sprite)
{
	sprites.push_back(sprite);
}

void RenderSystem::RemoveRenderable(Sprite* sprite)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (sprites[i] == sprite)
		{
			sprites.erase(sprites.begin() + i);
		}
	}
}

void RenderSystem::RenderRects()
{
	for (int i = 0; i < rects.size(); i++)
	{
		SDL_FRect renderedRect = *rects[i];
		renderedRect.x -= cam->offset.x;
		renderedRect.y -= cam->offset.y;
		SDL_RenderFillRectF(renderer, &renderedRect);
	}
}

void RenderSystem::RenderSprites()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		SDL_FRect renderedRect = sprites[i]->rect;
		renderedRect.x -= cam->offset.x;
		renderedRect.y -= cam->offset.y;

		SDL_RenderCopyExF(renderer, sprites[i]->texture, &sprites[i]->sourceRect, &renderedRect, sprites[i]->rotation, 0, SDL_FLIP_NONE);
	}
}