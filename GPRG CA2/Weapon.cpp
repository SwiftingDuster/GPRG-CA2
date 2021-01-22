#include "stdafx.h"
#include "Weapon.h"

// Default constructor. // This class is abstract and should be created with a derived class.
Weapon::Weapon() 
{
	isPlayerWeapon = false;
}

Entity* Weapon::GetWeaponOwner()
{
	return weaponOwner;
}

// Returns whether this weapon object belongs to the player. (Or the enemy)
bool Weapon::GetIsPlayerWeapon()
{
	return isPlayerWeapon;
}

// Declare that the current weapon object belongs to the player.
void Weapon::SetAsPlayerWeapon()
{
	isPlayerWeapon = true;
}
