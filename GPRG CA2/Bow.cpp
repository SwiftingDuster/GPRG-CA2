#include "stdafx.h"
#include "Bow.h"

Bow::Bow(Entity* ownerEntity, float cooldown)
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::bowTexture);
	
	SetOrigin(10, 10);

	this->weaponOwner = ownerEntity;
	this->cooldown = cooldown;
	this->timeToNextUse = 0;
	this->damage = 40;
}

void Bow::Use(Vector2f forwardVector)
{
	if (timeToNextUse > 0 || !Game::GetInstance()->GetGameRunning())
		return;
	else
		this->timeToNextUse = cooldown;

	if (isPlayerWeapon) // Method is called from a player's weapon object
	{
		if (Game::GetInstance()->GetPlayer()->UseArrow())
		{
			Arrow * arrow = new Arrow(this, this->damage, forwardVector); // Create an arrow and provide the source (Bow)
			arrow->heapReference = arrow; // Ensure its heap reference is not lost once this method ends
			Game::GetInstance()->activeProjectiles.push_back(arrow);
			Game::GetInstance()->PlayBowShootSound();
		}
	}
	else // Method is called from an enemy's weapon object
	{
		Arrow * arrow = new Arrow(this, this->damage / 5, forwardVector, 300.f); // Create an arrow and provide the source (Bow)
		arrow->heapReference = arrow; // Ensure its heap reference is not lost once this method ends
		Game::GetInstance()->activeProjectiles.push_back(arrow);
		Game::GetInstance()->PlayBowShootSound();
	}
}

void Bow::Cooldown(float deltaTime)
{
	if (timeToNextUse <= 0) return;
	this->timeToNextUse -= deltaTime;
}