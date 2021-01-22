#include "stdafx.h"
#include "ArrowPack.h"

ArrowPack::ArrowPack()
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::arrowPackTexture);
	player = Game::GetInstance()->GetPlayer();
	this->SetOrigin(8, 8);
}

void ArrowPack::PickUp()
{
	player->RestoreArrows(Player::MaxArrowAmmo / 2);
	Disable();
}