#pragma once
#include "GameObject.h"
#include "PoolManager.h"

class Game;
class Player : public GameObject
{
public:
	Player(Game* game, const std::string& texPath = playerTexPath);
	Player(float x, float y, Game* game, const std::string& texPath = playerTexPath);
	Player(Vector2 pos, Game* game, const std::string& texPath = playerTexPath);

	virtual void Update(double dt) override;
	virtual void OnCollision(GameObject* other) override;
	virtual void Reset(Vector2 pos) override;
	void CheckBounds(int width, int height, int buffer = 0);

	const float acceleration = 200.0f;
	const float deceleration = 300.0f;
	const float shootCooldown = 0.2f;
	const float maxSpeed = 200.0f;
	const float rotationSpeed = 200.0f;
	float shootTimer = 0.0f;
	Vector2 currentVelocity = Vector2(0, 0);
	Game* game = nullptr;
};

