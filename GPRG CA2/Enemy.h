#pragma once
#include "Entity.h"
#include "Weapon.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	// Internal Processing
	int uniqueEnemyId;
	Enemy * heapReference;

	// FSM Controller
	enum EnemyState { Idling, Chasing, Attacking, Dead };
	EnemyState enemyState = EnemyState::Chasing;

	// Game Interactions
	void EquipWeapon(Weapon * weapon);
	void ReceiveDamage(int amount);

	Weapon * GetBowPointer();

	void Update(float deltaTime, float enemySpeed);
	void Destroy();
private:
	const float MaxDetectionRange = 1000.f;
	const float MaxAttackRange = 400.f;

	Weapon * bow = new Bow(this, 1.f);

	Player * targetPlayer = nullptr;
	Weapon * activeWeapon = nullptr;

	void CalculateRotation();

	void Idle();
	void Chase(float deltaTime, float enemySpeed);
	void Attack();
	void Die();
};