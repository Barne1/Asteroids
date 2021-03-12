#include "CollisionManager.h"
#include "PoolManager.h"
#include "Bullet.h"
#include "SmallAsteroid.h"

void CollisionManager::CheckCollisions(GameObject* player)
{
	std::vector<GameObject*> gameObjects;
	gameObjects.push_back(player);
	for (auto o : PoolManager::bulletPool->activeObjects)
	{
		gameObjects.push_back(o);
	}
	for (auto o : PoolManager::smallAsteroidPool->activeObjects)
	{
		gameObjects.push_back(o);
	}

	for(int i = 0; i < gameObjects.size(); i++)
	{
		GameObject* leftObject = gameObjects[i];
		if (!leftObject->active)
			continue;

		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			GameObject* rightObject = gameObjects[j];
			if (!rightObject->active)
				continue;

			if (leftObject->pos.SqrDistanceTo(rightObject->pos) <
			(leftObject->colliderRadius + rightObject->colliderRadius) * (leftObject->colliderRadius + rightObject->colliderRadius)) // squared to avoid having to do sqrt
			{
				
				if (!HasCollisionPair(std::pair<GameObject::Type, GameObject::Type>(leftObject->type, rightObject->type)))
					continue;

				leftObject->OnCollision(rightObject);
				rightObject->OnCollision(leftObject);
			}
		}
	}
}

bool CollisionManager::HasCollisionPair(std::pair<GameObject::Type, GameObject::Type> collisionPair)
{
	std::pair<GameObject::Type, GameObject::Type> otherPair(collisionPair.second, collisionPair.first);
	if ((collisionPairs.find(collisionPair) != collisionPairs.end()) 
	|| collisionPairs.find(otherPair) != collisionPairs.end()) // Checks if set contains the pair or the pair in the other order
		return true;

	return false;
}

void CollisionManager::AddCollisionPair(std::pair<GameObject::Type, GameObject::Type> pair)
{
	collisionPairs.insert(pair);
}
