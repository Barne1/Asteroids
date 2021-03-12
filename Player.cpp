#include "Player.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "game.h"

Player::Player(Game* game, const std::string& texPath) : game(game),
	GameObject(ResourceManager::GetTextureData(texPath), PLAYER)
{
}

Player::Player(float x, float y, Game* game, const std::string& texPath): game(game),
	GameObject(x, y, ResourceManager::GetTextureData(texPath), PLAYER)
{
}

Player::Player(Vector2 pos, Game* game, const std::string& texPath): game(game),
	GameObject(pos, ResourceManager::GetTextureData(texPath), PLAYER)
{
}

void Player::Update(double dt)
{
	shootTimer -= dt;
	ForwardBack fb = InputHandler::GetForwardBack();
	if(fb == ForwardBack::FORWARD)
	{
		if(currentVelocity.Dot(forward) < maxSpeed)
			currentVelocity += acceleration * forward * dt;
	}
	else if(fb == ForwardBack::BACK)
	{
		if(currentVelocity.Dot(-forward) < maxSpeed)
			currentVelocity -= deceleration * forward * dt;
	}
	LeftRight lr = InputHandler::GetLeftRight();
	if(lr == LeftRight::LEFT)
	{
		forward = forward.Rotate(-rotationSpeed * dt).Normalize();
	}
	else if(lr == LeftRight::RIGHT)
	{
		forward = forward.Rotate(rotationSpeed * dt).Normalize();
	}

	if (InputHandler::GetShoot() && shootTimer <= 0)
	{
		shootTimer = shootCooldown;
		Bullet* b = PoolManager::bulletPool->GetNextObject();
		b->forward = forward;
		b->pos = pos + forward*40;
		std::cout << "pew pew" << std::endl;
	}

	pos += currentVelocity * dt;
}

void Player::OnCollision(GameObject* other)
{
	switch(other->type)
	{
	default: break;
	case ASTEROID: active = false; game->gameOver = true;
		break;
	}
}

void Player::Reset(Vector2 pos)
{
	GameObject::Reset(pos);
	currentVelocity = Vector2(0, 0);
	active = true;
}

void Player::CheckBounds(int width, int height, int buffer)
{
	if (pos.x > width + buffer)
		pos.x = 0 - buffer*0.5;
	else if(pos.x < 0 - buffer)
		pos.x = width + buffer*0.5;

	if (pos.y > height + buffer)
		pos.y = 0 - buffer*0.5;
	else if (pos.y < 0 - buffer)
		pos.y = height + buffer*0.5;
}
