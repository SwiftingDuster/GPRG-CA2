#pragma once
#include "GameObject.h"
#include "Extension.h"

class Entity : public GameObject
{
public:
	const int MaxHealth = 100;

	Entity::Entity();

	int GetHealth();

	void RestoreHealth(int amount);
	void SetHealth(int health);

	Vector2f lastMovement;

	virtual void Attack() = 0;
	virtual void ReceiveDamage(int amount) = 0;
	virtual void Die() = 0;
protected:
	int health;
};
