#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
class SmallAsteroid : public GameObject
{
public:
	SmallAsteroid(const std::string& texPath = asteroidTexPath);
	SmallAsteroid(Vector2 pos, const std::string& texPath = asteroidTexPath);
	SmallAsteroid(float x, float y, const std::string& texPath = asteroidTexPath);

	const int speed = 100;
	virtual void Update(double dt) override;
	virtual void OnCollision(GameObject* other) override;
	ObjectPool<SmallAsteroid>* pool;
};

