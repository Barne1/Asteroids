#include "game.h"
#include "Vector2.h"
#include <iostream>
#include "PoolManager.h"
#include "utility.h"

Player* Game::player = nullptr;

Game::Game(const char* title, int width, int height, bool fullscreen)
	: isRunning(true)
	, width(width), height(height)
	, asteroidSpawner(width, height)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if(window == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	isRunning = true;
	
	ResourceManager::LoadAll(renderer);
	PoolManager::Init();

	player = new Player(Vector2(width/2, height/2), this);
	player->active = true;
	collisionManager.AddCollisionPair(std::pair<GameObject::Type, GameObject::Type>(GameObject::PLAYER, GameObject::ASTEROID));
	collisionManager.AddCollisionPair(std::pair<GameObject::Type, GameObject::Type>(GameObject::BULLET, GameObject::ASTEROID));
	collisionManager.AddCollisionPair(std::pair<GameObject::Type, GameObject::Type>(GameObject::ASTEROID, GameObject::ASTEROID));
}

Game::~Game()
{
	SDL_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: isRunning = false; break;
	case SDL_KEYDOWN: InputHandler::UpdateKeyboardState(); break;
	case SDL_KEYUP: InputHandler::UpdateKeyboardState(); break;
	default: break;
	}
}

void Game::Update(double deltaTime)
{
	const int OBJECT_BOUNDS_BUFFER = 50;
	player->CheckBounds(width, height, OBJECT_BOUNDS_BUFFER);
	player->UpdateBase(deltaTime);
	
	for (auto o : PoolManager::smallAsteroidPool->activeObjects)
	{
		if(!Utility::IsInBounds(o->pos, width, height, OBJECT_BOUNDS_BUFFER))
		{
			o->active = false;
			continue;
		}
		o->UpdateBase(deltaTime);
	}
	asteroidSpawner.Update(deltaTime);

	if (gameOver)
	{
		if (InputHandler::GetRestart())
			Restart();
	}
	else
	{
		for (auto o : PoolManager::bulletPool->activeObjects)
		{
			if(!Utility::IsInBounds(o->pos, width, height, OBJECT_BOUNDS_BUFFER))
			{
				o->active = false;
				continue;
			}
			o->UpdateBase(deltaTime);
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	player->Render(renderer);
	for (auto o : PoolManager::bulletPool->activeObjects)
	{
		o->Render(renderer);
	}
	for (auto o : PoolManager::smallAsteroidPool->activeObjects)
	{
		o->Render(renderer);
	}
	if (gameOver)
	{
		SDL_Rect dst = *ResourceManager::GetTextureData(gameOverTexPath)->rect;
		dst.x = width / 2;
		dst.y = height / 2;
		dst = Utility::GetCenteredRect(dst);
		SDL_RenderCopy(
			renderer, 
			ResourceManager::GetTextureData(gameOverTexPath)->texture,
			ResourceManager::GetTextureData(gameOverTexPath)->rect,
			&dst);
	}
	SDL_RenderPresent(renderer);
}

void Game::CheckCollisions()
{
	collisionManager.CheckCollisions(player);
}


void Game::Restart()
{
	player->Reset(Vector2(width/2, height/2));
	PoolManager::smallAsteroidPool->activeObjects.clear();
	PoolManager::bulletPool->activeObjects.clear();
	gameOver = false;
}

