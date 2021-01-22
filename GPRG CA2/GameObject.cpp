#include "stdafx.h"
#include "GameObject.h"

// GameObject Default Constructor. Every object in the scene should inherit from this class.
GameObject::GameObject()
{
	isActive = true;
	enableDraw = true;
}

// Load object's appropriate texture and sprite.
void GameObject::LoadTextureAndSprite(Texture _texture)
{
	this->texture = _texture;
	this->sprite.setTexture(this->texture);
}

// Set the position.
void GameObject::SetPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

// Set the position.
void GameObject::SetPosition(Vector2f location)
{
	this->sprite.setPosition(location);
}

// Set the position.
void GameObject::SetPosition(Vector2i location)
{
	this->sprite.setPosition(Vector2f(location));
}

// Set the rotation.
void GameObject::SetRotation(float angle)
{
	this->sprite.setRotation(angle);
}

// Set the origin.
void GameObject::SetOrigin(float x, float y)
{
	this->sprite.setOrigin(x, y);
}

// Get the position.
Vector2f GameObject::GetPosition()
{
	return this->sprite.getPosition();
}

// Get the rotation.
float GameObject::GetRotation()
{
	return this->sprite.getRotation();
}

// Get the global bounderies of object.
FloatRect GameObject::GetCollider()
{
	return this->sprite.getGlobalBounds();
}

// Moves the gameobject.
void GameObject::Move(Vector2f &vector)
{
	this->sprite.move(vector);
}

// Moves the gameobject.
void GameObject::Move(float x, float y)
{
	this->sprite.move(x, y);
}

// Set gameobject as inactive and don't render it.
void GameObject::Disable()
{
	this->isActive = false;
	this->enableDraw = false;
}