#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "SmallAsteroid.h"
#include "utility.h"
#include "InputHandler.h"
#include "CollisionManager.h"
#include "AsteroidSpawner.h"


class Game
{
public:
	Game() = delete;
	Game(const char* title, int width, int height, bool fullscreen);
	~Game();

	void HandleEvents();
	void Update(double deltaTime);
	void Render();
	void CheckCollisions();

	bool Running() { return isRunning; }

	bool gameOver = false;
	void Restart();
private:
	int width;
	int height;
	bool isRunning;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	CollisionManager collisionManager;
	AsteroidSpawner asteroidSpawner;
	static Player* player;
};

