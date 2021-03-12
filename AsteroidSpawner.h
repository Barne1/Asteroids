#pragma once
#include <random>

class AsteroidSpawner
{
public:
	AsteroidSpawner(int screenWidth, int screenHeight);
	void Update(double deltaTime);
private:
	void SpawnSmallAsteroid();
	float spawnDelay = 0.1f;
	float spawnTimer = 0.0f;
	int screenWidth;
	int screenHeight;
	int spawnOffset = 500;
	std::mt19937 gen;
	float GetRandom(float min = -1.0f, float max = 1.0f);
};