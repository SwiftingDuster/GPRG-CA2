#pragma once
#include "Ammo.h"

class Arrow : public Ammo
{
public:
	Arrow(Bow * source, int damage, Vector2f forward, float projectileSpeed = 700.f);

	void Update(float deltaTime);
	void Destroy();
};