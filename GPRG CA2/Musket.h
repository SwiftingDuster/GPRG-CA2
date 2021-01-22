#pragma once
#include "Weapon.h"

class Musket : public Weapon
{
public:
	Musket(Entity * ownerEntity, float cooldown = 0.3f);

	void Use(Vector2f forwardVector);
	void Cooldown(float deltaTime);
};