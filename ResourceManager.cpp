#include "ResourceManager.h"
#include "utility.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <memory>

std::map<std::string, std::shared_ptr<TextureData>> ResourceManager::textures;

void ResourceManager::LoadAll(SDL_Renderer* rend)
{
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) // Returns the flags that are successfully initialized
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	
	
	std::shared_ptr<TextureData> playerTex = CreateTexture(playerTexPath, rend);
	std::shared_ptr<TextureData> bulletTex = CreateTexture(bulletTexPath, rend);
	std::shared_ptr<TextureData> asteroidTex = CreateTexture(asteroidTexPath, rend);
	std::shared_ptr<TextureData> gameOverTex = CreateTexture(gameOverTexPath, rend);
	
	textures[playerTexPath] = playerTex;
	textures[bulletTexPath] = bulletTex;
	textures[asteroidTexPath] = asteroidTex;
	textures[gameOverTexPath] = gameOverTex;

	IMG_Quit(); // No longer need image reading resources
}

std::shared_ptr<TextureData> ResourceManager::CreateTexture(std::string path, SDL_Renderer* rend)
{
	SDL_Surface* tempSurf = IMG_Load(path.c_str());
	if(tempSurf == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return NULL;
	}
	else
	{
		std::cout << "Texture at: " << path << " Successfully Loaded" << std::endl;
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, tempSurf);
	SDL_FreeSurface(tempSurf);
	
	if (tex == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return NULL;
	}
	else
	{
		std::cout << "Texture conversion for: " << path << " Successfully Converted" << std::endl;
	}
	
	std::shared_ptr<TextureData> data = std::make_shared<TextureData>();
	data->rect = new SDL_Rect;
	data->rect->h = tempSurf->h;
	data->rect->w = tempSurf->w;
	data->rect->x = 0;
	data->rect->y = 0;
	data->texture = tex;
	return data;
}

std::shared_ptr<TextureData> ResourceManager::GetTextureData(std::string path)
{
	return textures[path];
}