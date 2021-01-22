#include "stdafx.h"
#include "HealthPack.h"

HealthPack::HealthPack()
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::healthPackTexture);
	player = Game::GetInstance()->GetPlayer();
	this->SetOrigin(8, 8);
}

void HealthPack::PickUp()
{
	player->RestoreHealth(30);
	Disable();
}