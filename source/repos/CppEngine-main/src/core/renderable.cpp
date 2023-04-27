#include <core/renderable.h>

Renderable::Renderable(SDL_Texture* tex, std::string filePath)
{
	texture = tex;
	path = filePath;
	refCount = 1;
}