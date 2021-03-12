#pragma once
#include <iostream>
#include <map>
#include "SDL.h"
#include "TextureData.h"

const static std::string playerTexPath = "Assets/playertex.png";
const static std::string bulletTexPath = "Assets/bullettex.png";
const static std::string asteroidTexPath = "Assets/asteroidtex.png";
const static std::string gameOverTexPath = "Assets/gameover.png";

class ResourceManager
{
public:
	static void LoadAll(SDL_Renderer* rend);
	static std::shared_ptr<TextureData> GetTextureData(std::string texPath);
	static std::shared_ptr<TextureData> CreateTexture(std::string path, SDL_Renderer* rend);
	static std::map<std::string, std::shared_ptr<TextureData>> textures;
};

