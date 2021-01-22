#include "stdafx.h"
#include "BulletPack.h"

BulletPack::BulletPack()
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::bulletPackTexture);
	player = Game::GetInstance()->GetPlayer();
	this->SetOrigin(8, 8);
}

void BulletPack::PickUp()
{
	player->RestoreBullets(Player::MaxMusketAmmo / 2);
	Disable();
}