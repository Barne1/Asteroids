#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include <functional>

class Bullet : public GameObject
{
public:
	Bullet(const std::string& texPath = bulletTexPath);
	Bullet(float x, float y, void(*RemoveFromListFcn)(Bullet*), const std::string& texPath = bulletTexPath);
	Bullet(Vector2 pos, void(*RemoveFromListFcn)(Bullet*), const std::string& texPath = bulletTexPath);

	const float speed = 500;

	virtual void Update(double dt) override;
	virtual void OnCollision(GameObject* other) override;
	ObjectPool<Bullet>* pool;
};

