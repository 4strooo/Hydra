#pragma once
#include <SDL.h>
#include <string>

class Renderable
{
public:
	Renderable(SDL_Texture* tex, std::string path);
	SDL_Texture* texture;
	std::string path;
	int refCount;
};