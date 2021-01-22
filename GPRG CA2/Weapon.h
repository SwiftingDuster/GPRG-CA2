#pragma once
#include "Entity.h"

// This class is a generic base weapon class that all weapon objects should inherit from.
class Weapon : public GameObject
{
public:
	// Default constructor. This class is abstract and should be created with a derived class.
	Weapon();

	Entity* GetWeaponOwner();

	// Returns whether this weapon object belongs to the player. (False if it's enemy)
	bool GetIsPlayerWeapon();
	
	// Declare that the current weapon object belongs to the player.
	void SetAsPlayerWeapon();

	void SetAttackPower(int amount)
	{
		this->damage = amount;
	}

	virtual void Use(Vector2f forwardVector) = 0;
	virtual void Cooldown(float deltaTime) = 0;
protected:
	int damage;
	float cooldown;
	float timeToNextUse;

	bool isPlayerWeapon;
	Entity * weaponOwner = nullptr;
};