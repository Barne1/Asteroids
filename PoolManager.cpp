#include "PoolManager.h"
#include "SmallAsteroid.h"
#include "Bullet.h"

ObjectPool<Bullet>* PoolManager::bulletPool;
ObjectPool<SmallAsteroid>* PoolManager::smallAsteroidPool;

void PoolManager::Init()
{
	bulletPool = new ObjectPool<Bullet>();
	smallAsteroidPool = new ObjectPool<SmallAsteroid>();
}