#pragma once

// This class is a generic projectile class that all projectile objects should inherit from.
class Ammo : public GameObject
{
public:
	// Default constructor. This class is abstract and should be created with a derived class.
	Ammo();

	int uniqueAmmoID;
	Ammo * heapReference = nullptr;
	
	int damage;

	Weapon* GetSourceWeapon();

	virtual void Update(float deltaTime) = 0;

	virtual void Destroy() = 0;
protected:
	float projectileSpeed;

	Vector2f forward;

	Weapon * sourceWeapon;
};