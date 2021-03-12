#pragma once
#include <memory>

class SDL_Texture;
class SDL_Rect;

//using texData_ptr = std::shared_ptr<TextureData>;

struct TextureData
{
	SDL_Rect* rect;
	SDL_Texture* texture;
};

