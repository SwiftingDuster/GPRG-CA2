#include "stdafx.h"
#include "Ammo.h"

Ammo::Ammo()
{
	// Generate unique id
	bool isUnique;
	do {
		isUnique = true;
		uniqueAmmoID = rand() % 1000 + 1; // 1 - 1000

		list<Ammo*>::iterator iter = Game::GetInstance()->activeProjectiles.begin();
		while (iter != Game::GetInstance()->activeProjectiles.end() && !isUnique)
		{
			if ((*iter)->uniqueAmmoID == uniqueAmmoID)
			{
				isUnique = false;
				break;
			}
		}
	} while (!isUnique);
}

// Returns the weapon that created this projectile object.
Weapon * Ammo::GetSourceWeapon()
{
	return sourceWeapon;
}