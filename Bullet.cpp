#include "Bullet.h"

Bullet::Bullet(const std::string& texPath)
	: GameObject(ResourceManager::GetTextureData(texPath), BULLET)
{
}

Bullet::Bullet(float x, float y, void(*RemoveFromListFcn)(Bullet*), const std::string& texPath)
	: GameObject(x,y,ResourceManager::GetTextureData(texPath), BULLET)
{
}

Bullet::Bullet(Vector2 pos, void(*RemoveFromListFcn)(Bullet*), const std::string& texPath)
	: GameObject(pos, ResourceManager::GetTextureData(texPath), BULLET)
{
}

void Bullet::Update(double dt)
{
	pos += forward * speed * dt;
}

void Bullet::OnCollision(GameObject* other)
{
	switch(other->type)
	{
		case ASTEROID:
			pool->RemoveFromActive(this);
			break;
	}
	
}
