#pragma once
#include "Weapon.h"

class Bow : public Weapon
{
public:
	Bow(Entity * ownerEntity, float cooldown = 0.5f);

	void Use(Vector2f forwardVector);
	void Cooldown(float deltaTime);
};