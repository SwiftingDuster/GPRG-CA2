#pragma once
#include "Entity.h"
#include "Bow.h"
#include "Musket.h"
#include "Arrow.h"
#include "Bullet.h"

class Player : public Entity
{
public:
	const static int MaxLives = 3;
	const static int MaxArrowAmmo = 64;
	const static int MaxMusketAmmo = 24;

	Player();
	~Player();

	void SetMousePosition(Vector2i _mousePosition);

	int GetLives();
	int GetArrowsRemaining();
	int GetBulletsRemaining();
	Weapon* GetBowPointer();
	Weapon* GetMusketPointer();

	void EquipWeapon(Weapon * weapon);
	void RestoreArrows(int amount);
	void RestoreBullets(int amount);

	bool UseArrow(int amount = 1);
	bool UseBullet(int amount = 1);

	void Attack();
	void ReceiveDamage(int amount);
	void Die();
private:
	Vector2f mousePosition;
	int lives;

	Weapon * bow = new Bow(this);
	Weapon * musket = new Musket(this);

	int bowAmmo = MaxArrowAmmo;
	int musketAmmo = MaxMusketAmmo;

	Weapon * activeWeapon = nullptr;
};