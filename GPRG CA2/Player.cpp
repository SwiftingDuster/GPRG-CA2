#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::playerTexture);

	health = MaxHealth;
	lives = MaxLives;

	this->EquipWeapon(bow);
	bow->enableDraw = true;
	musket->enableDraw = false;

	SetPosition(Game::WindowSizeX / 2, Game::WindowSizeY / 2); // Center player on screen
	SetOrigin(12, 26);
}

Player::~Player()
{
	delete bow;
	delete musket;
}

// Set mouse position for weapon aiming and shooting
void Player::SetMousePosition(Vector2i _mousePosition)
{
	mousePosition = Vector2f(_mousePosition);
}

// Equips a weapon
void Player::EquipWeapon(Weapon * weapon)
{
	this->activeWeapon = weapon;
}

// Restores arrows by amouont.
void Player::RestoreArrows(int amount)
{
	this->bowAmmo += amount;

	if (bowAmmo > MaxArrowAmmo) bowAmmo = MaxArrowAmmo;
}

// Restores bullets by amount.
void Player::RestoreBullets(int amount)
{
	this->musketAmmo += amount;

	if (musketAmmo > MaxMusketAmmo) musketAmmo = MaxMusketAmmo;
}

// Attacks with current weapon.
void Player::Attack()
{
	Vector2f playerPosition = GetPosition();
	Vector2f direction = mousePosition - playerPosition;
	Extension::Normalize(direction);

	this->activeWeapon->Use(direction);
}

// Receive damage specified by amount.
void Player::ReceiveDamage(int amount)
{
	this->health -= amount;
}

// Death
void Player::Die()
{
	if (lives > 1)
	{
		for (auto enemy : Game::GetInstance()->activeEnemies)
		{
			enemy->Disable();
		}
		for (auto projectile : Game::GetInstance()->activeProjectiles)
		{
			if (projectile->heapReference != reinterpret_cast<Ammo*>(0xDDDDDDDD)) projectile->Disable();
		}
		lives--;
		SetHealth(100);
		SetPosition(Game::WindowSizeX / 2, Game::WindowSizeY / 2);
	}
	else
	{
		Game::GetInstance()->GameOver();
		lives = 3; // Reset lives
	}
}

int Player::GetLives()
{
	return lives;
}

int Player::GetArrowsRemaining()
{
	return bowAmmo;
}

int Player::GetBulletsRemaining()
{
	return musketAmmo;
}

// Decrease numbers of arrows left by amount. Amount is optional and defaults to 11. Returns true if deduction succeeds.
bool Player::UseArrow(int amount) // Currently uses max 1 at a time.
{
	if (bowAmmo >= 1 && (bowAmmo - amount) >= 0) // At least have one ammo and ammo count does not go below 0 after use.
	{
		this->bowAmmo -= amount;
		return true;
	}
	return false; // Not enough ammo.
}

// Decrease numbers of bullets left by amount. Amount is optional and defaults to 1. Returns true if deduction succeeds.
bool Player::UseBullet(int amount) // Currently uses max 1 at a time.
{
	if (musketAmmo >= 1 && (musketAmmo - amount) >= 0) // At least have one ammo and ammo count does not go below 0 after use.
	{
		this->musketAmmo -= amount;
		return true;
	}
	return false; // Not enough ammo.
}

Weapon * Player::GetBowPointer()
{
	return bow;
}

Weapon * Player::GetMusketPointer()
{
	return musket;
}