#include "stdafx.h"
#include "Arrow.h"
#include "ResourceHolder.h"

Arrow::Arrow(Bow* source, int damage, Vector2f forwardVector, float projectileSpeed)
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::arrowTexture);

	this->sourceWeapon = source;
	this->damage = damage;
	this->forward = forwardVector;
	this->projectileSpeed = projectileSpeed;

	SetPosition(source->GetPosition());
	this->SetRotation(this->sourceWeapon->GetWeaponOwner()->GetRotation());
	SetOrigin(0, 9);
}

void Arrow::Update(float deltaTime)
{
	if (forward != Vector2f(0, 0)) this->Move(forward * projectileSpeed * deltaTime);
}

void Arrow::Destroy()
{
	if (Game::GetInstance()->activeProjectiles.size() == 0) return;

	if (Game::GetInstance()->activeProjectiles.size() == 1)
	{
		Game::GetInstance()->activeProjectiles.clear();
		delete heapReference;
	}
	else
	{
		list<Ammo*>::iterator iter = Game::GetInstance()->activeProjectiles.begin();
		while (iter != Game::GetInstance()->activeProjectiles.end())
		{
			if ((*iter)->uniqueAmmoID == this->uniqueAmmoID)
			{
				// Remove itself from active projectiles list and free heap memory
				iter = Game::GetInstance()->activeProjectiles.erase(iter);
				delete heapReference;
				break;
			}
			else
			{
				++iter;
			}
		}
	}
}