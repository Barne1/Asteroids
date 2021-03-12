#include "GameObject.h"

GameObject::GameObject(Vector2 pos, std::shared_ptr<TextureData> texData, Type t)
	:pos(pos)
	, textureData(texData)
	, colliderRadius(texData->rect->w / 2)
	, type(t)
{
}

GameObject::GameObject(std::shared_ptr<TextureData> texData, Type t)
	: textureData(texData)
	, colliderRadius(texData->rect->w / 2)
	, type(t)
{
}

GameObject::GameObject(float x, float y, std::shared_ptr<TextureData> texData, Type t)
	: pos(x, y)
	, textureData(texData)
	, colliderRadius(texData->rect->w / 2)
	, type(t)
{
}

void GameObject::Render(SDL_Renderer* renderer)
{
	if (!active)
		return;
	SDL_Rect posRect = *(textureData->rect);
	posRect.x = pos.x;
	posRect.y = pos.y;
	SDL_Point center;
	center.x = posRect.w/2;
	center.y = posRect.h/2;

	posRect = Utility::GetCenteredRect(posRect);
	SDL_RenderCopyEx(renderer, textureData->texture, textureData->rect, &posRect, -forward.GetAngle()+180, &center, SDL_FLIP_NONE);
}

void GameObject::Reset(Vector2 pos)
{
	this->pos = pos;
	forward = Vector2::Up();
}

void GameObject::Update(double dt)
{
}

void GameObject::OnCollision(GameObject* other)
{
}

void GameObject::UpdateBase(double dt)
{
	if (!active)
		return;
	Update(dt);
}
