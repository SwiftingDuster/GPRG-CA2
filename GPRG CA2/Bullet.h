#pragma once
#include "Ammo.h"

class Bullet : public Ammo
{
public:
	Bullet(Musket * source, int damage, Vector2f forwardVector, float projectileSpeed = 1200.f);

	void Update(float deltaTime);
	void Destroy();
};