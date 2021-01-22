#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{

}

int Entity::GetHealth()
{
	return health;
}

void Entity::RestoreHealth(int amount)
{
	if (amount < 0) amount = 0;
	this->health += amount;
	if (this->health > MaxHealth)
		this->health = MaxHealth;
}

void Entity::SetHealth(int health)
{
	if (health < 0) health = 0;
	this->health = health;
	if (this->health > MaxHealth)
		this->health = MaxHealth;
}