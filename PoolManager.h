#pragma once
#include "ObjectPool.h"
#include <vector>

class Bullet;
class SmallAsteroid;
class PoolManager
{
public:
	static ObjectPool<Bullet>* bulletPool;
	static ObjectPool<SmallAsteroid>* smallAsteroidPool;
	static void Init();
};