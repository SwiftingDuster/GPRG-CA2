#include "stdafx.h"
#include "Musket.h"

Musket::Musket(Entity* ownerEntity, float cooldown)
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::musketTexture);

	this->weaponOwner = ownerEntity;
	this->cooldown = cooldown;
	this->timeToNextUse = 0;
	this->damage = 90;
}

void Musket::Use(Vector2f forwardVector)
{
	if (timeToNextUse > 0 || !Game::GetInstance()->GetGameRunning())
		return;
	else
		this->timeToNextUse = cooldown;

	if (isPlayerWeapon) // Method is called from a player's weapon object
	{
		if (Game::GetInstance()->GetPlayer()->UseBullet())
		{
			Bullet * bullet = new Bullet(this, damage, forwardVector); // Create a bullet and provide the source (Bow)
			bullet->heapReference = bullet; // Ensure its heap reference is not lost once this method ends
			Game::GetInstance()->activeProjectiles.push_back(bullet);
			Game::GetInstance()->PlayMusketShootSound();
		}
	}
	else // Method is called from an enemy's weapon object
	{
		Bullet * bullet = new Bullet(this, damage / 5, forwardVector, 600.f); // Create a bullet and provide the source (Bow)
		bullet->heapReference = bullet; // Ensure its heap reference is not lost once this method ends
		Game::GetInstance()->activeProjectiles.push_back(bullet);
		Game::GetInstance()->PlayMusketShootSound();
	}
}

void Musket::Cooldown(float deltaTime)
{
	if (timeToNextUse <= 0) return;
	this->timeToNextUse -= deltaTime;
}