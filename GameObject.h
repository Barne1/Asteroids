#pragma once
#include "Vector2.h"
#include "TextureData.h"
#include "ResourceManager.h"
#include "SDL.h"
#include "utility.h"

class GameObject
{
public:
	enum Type
	{
		PLAYER,
		BULLET,
		ASTEROID
	};
	GameObject() = delete;
	GameObject(std::shared_ptr<TextureData> texData, Type);
	GameObject(float x, float y, std::shared_ptr<TextureData> texData, Type);
	GameObject(Vector2 pos, std::shared_ptr<TextureData> texData, Type);

	virtual void Render(SDL_Renderer* renderer);
	virtual void Reset(Vector2 pos = Vector2(0,0));
	virtual void Update(double dt);
	virtual void OnCollision(GameObject* other);
	void UpdateBase(double dt);

	Vector2 pos = Vector2(0,0);
	Vector2 forward = Vector2::Up();
	int colliderRadius = 0.0f;
	bool active = true;
	
	Type type;
protected:
	
	std::shared_ptr<TextureData> textureData;
};

