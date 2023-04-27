#pragma once
#include <SDL.h>
#include <core/subsystem.h>
#include <string>
#include <vector>
#include <core/renderable.h>

class AssetManager : public SubSystem
{
public:
	SDL_Texture* LoadTexture(std::string path);
	void Dereference(SDL_Texture* texture);
private:
	std::vector<Renderable*> tempTextures;
};