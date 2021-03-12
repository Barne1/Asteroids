#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(const std::string& texPath) : GameObject(ResourceManager::GetTextureData(texPath), ASTEROID)
{
}

SmallAsteroid::SmallAsteroid(Vector2 pos, const std::string& texPath) : GameObject(pos, ResourceManager::GetTextureData(texPath), ASTEROID)
{
}

SmallAsteroid::SmallAsteroid(float x, float y, const std::string& texPath) : GameObject(x,y, ResourceManager::GetTextureData(texPath), ASTEROID)
{
}

void SmallAsteroid::Update(double dt)
{
	pos += forward * dt * speed;
}

void SmallAsteroid::OnCollision(GameObject* other)
{
	if (other->type == BULLET)
	{
		pool->RemoveFromActive(this);
	}
	else if(other->type == ASTEROID)
	{
		forward = (forward - (other->pos - pos)).Normalize();
	}
}
