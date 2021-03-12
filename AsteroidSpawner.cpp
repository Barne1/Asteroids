#include "AsteroidSpawner.h"
#include "SmallAsteroid.h"
#include "PoolManager.h"
#include <chrono>

AsteroidSpawner::AsteroidSpawner(int screenWidth, int screenHeight)
	: screenWidth(screenWidth)
	, screenHeight(screenHeight)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	gen = std::mt19937(seed);
}

void AsteroidSpawner::Update(double deltaTime)
{
	spawnTimer -= deltaTime;
	if(spawnTimer <= 0.0f)
	{
		SpawnSmallAsteroid();
		spawnTimer = spawnDelay;
	}
}

void AsteroidSpawner::SpawnSmallAsteroid()
{
	Vector2 centerOfScreen(screenWidth * 0.5f, screenHeight * 0.5f);

	SmallAsteroid* newSpawn = PoolManager::smallAsteroidPool->GetNextObject();
	float randX = GetRandom(-1.0f, 1.0f);
	float randY = GetRandom(-1.0f, 1.0f);
	Vector2 randomOffset(randX, randY);
	randomOffset = randomOffset.Normalize();
	randomOffset = randomOffset * (screenWidth * 0.7f);
	newSpawn->pos = centerOfScreen + randomOffset;

	float randScreenX = GetRandom(-1.0f, 1.0f);
	randScreenX *= screenWidth;
	float randScreenY = GetRandom(-1.0f, 1.0f);
	randScreenY *= screenHeight;
	Vector2 randomScreenPoint(randScreenX, randScreenY);
	newSpawn->forward = (randomScreenPoint - newSpawn->pos).Normalize();
}

float AsteroidSpawner::GetRandom(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);

}
