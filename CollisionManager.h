#pragma once
#include <set>
#include <utility>
#include <vector>
#include "GameObject.h"

class CollisionManager
{
public:
	void CheckCollisions(GameObject* player);
	void AddCollisionPair(std::pair<GameObject::Type, GameObject::Type> pair);
private:
	bool HasCollisionPair(std::pair<GameObject::Type, GameObject::Type> collisionPair);
	std::set<std::pair<GameObject::Type, GameObject::Type>> collisionPairs;	
};

