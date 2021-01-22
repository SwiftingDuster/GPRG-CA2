#include "stdafx.h"
#include "Enemy.h"
#include "HealthPack.h"
#include "ArrowPack.h"
#include "BulletPack.h"

Enemy::Enemy()
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::enemyTexture);
	this->targetPlayer = Game::GetInstance()->GetPlayer();

	this->EquipWeapon(bow);

	// Generate unique id
	bool isUnique;
	do {
		isUnique = true;
		uniqueEnemyId = rand() % 1000 + 1; // 1 - 1000

		list<Enemy*>::iterator iter = Game::GetInstance()->activeEnemies.begin();
		while (iter != Game::GetInstance()->activeEnemies.end() && !isUnique)
		{
			if ((*iter)->uniqueEnemyId == uniqueEnemyId)
			{
				isUnique = false;
				break;
			}
		}
	} while (!isUnique);

	SetPosition(Game::GetInstance()->enemySpawnPoints[rand() % 6]);
	SetOrigin(12, 26);

	this->health = 100;
}

Enemy::~Enemy()
{
	delete bow;
}

void Enemy::EquipWeapon(Weapon * weapon)
{
	activeWeapon = weapon;
}

void Enemy::Update(float deltaTime, float enemySpeed)
{
	if (this->health <= 0) enemyState = EnemyState::Dead;
	switch (enemyState)
	{
	case EnemyState::Idling:
		Idle();
		break;
	case EnemyState::Chasing:
		Chase(deltaTime, enemySpeed);
		CalculateRotation();
		break;
	case EnemyState::Attacking:
		Attack();
		CalculateRotation();
		break;
	case EnemyState::Dead:
		Die();
		break;
	}
}

void Enemy::CalculateRotation()
{
	Vector2f playerLocation = targetPlayer->GetPosition();
	Vector2f enemyLocation = GetPosition();
	float angleToPlayer = (atan2(playerLocation.y - enemyLocation.y, playerLocation.x - enemyLocation.x) * 180.f) / 3.141f;
	SetRotation(angleToPlayer);
}

void Enemy::Idle()
{
	float distanceFromPlayer = Extension::GetMagnitude(targetPlayer->GetPosition() - this->GetPosition());
	if (distanceFromPlayer <= MaxDetectionRange)
	{
		enemyState = EnemyState::Chasing;
	}
}

void Enemy::Chase(float deltaTime, float enemySpeed)
{
	float distanceFromPlayer = Extension::GetMagnitude(targetPlayer->GetPosition() - this->GetPosition());
	if (distanceFromPlayer <= MaxAttackRange)
	{
		enemyState = EnemyState::Attacking;
	}
	else if (distanceFromPlayer > MaxDetectionRange)
	{
		enemyState = EnemyState::Idling;
	}
	Vector2f direction = targetPlayer->GetPosition() - this->GetPosition();
	Extension::Normalize(direction);
	lastMovement = direction * enemySpeed * deltaTime;
	this->Move(lastMovement);
}

void Enemy::Attack()
{
	float distanceFromPlayer = Extension::GetMagnitude(targetPlayer->GetPosition() - this->GetPosition());
	if (distanceFromPlayer > MaxAttackRange)
	{
		enemyState = EnemyState::Chasing;
		if (distanceFromPlayer > MaxDetectionRange)
		{
			enemyState = EnemyState::Idling;
		}
	}
	else
	{
		Vector2f enemyPosition = GetPosition();
		Vector2f playerPosition = Game::GetInstance()->GetPlayer()->GetPosition();
		Vector2f direction = playerPosition - enemyPosition;
		Extension::Normalize(direction);

		this->activeWeapon->Use(direction);
	}
}

// Enemy death, chance to drop loot and 
void Enemy::Die()
{
	// 1. Increase score
	Game::GetInstance()->IncreaseScore();

	// 2. Chance to generate a random drop
	int dropCount = 0; // How many drops (Up to 2)
	int dice1 = rand() % 5 + 1; // Get a number 1-5
	int dice2 = rand() % 5 + 1; // Get a number 1-5
	int dice3 = rand() % 5 + 1; // Get a number 1-5
	if (dice1 == dice2 || dice1 == dice3 || dice2 == dice3) // (12% chance)
	{
		dropCount = 1;
		if (dice1 == dice2 == dice3) // (8% chance)
		{
			dropCount = 2;
		}
	}

	switch (dropCount)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		// Randomize loot: Generate a 0, 1 or 2.
		// 0 = Drop Health, 1 = Drop Arrows, 2 = Drop Bullets
		int dropType = rand() % 3;
		Loot * drop;
		switch (dropType)
		{
		case 0:
			drop = new HealthPack();
			break;
		case 1:
			drop = new ArrowPack();
			break;
		case 2:
			drop = new BulletPack();
			break;
		}
		drop->SetPosition(this->GetPosition());
		drop->heapReference = drop;
		Game::GetInstance()->activeLoots.push_back(drop);
		break;
	}
	case 2:
	{
		// Randomize loot: Generate a 0, 1 or 2.
		// 0 = Drop Health, 1 = Drop Arrows, 2 = Drop Bullets
		int dropType1 = rand() % 3;
		int dropType2 = rand() % 3;
		Loot * drop1;
		Loot * drop2;
		switch (dropType1)
		{
		case 0:
			drop1 = new HealthPack();
			break;
		case 1:
			drop1 = new ArrowPack();
			break;
		case 2:
			drop1 = new BulletPack();
			break;
		}
		switch (dropType2)
		{
		case 0:
			drop2 = new HealthPack();
			break;
		case 1:
			drop2 = new ArrowPack();
			break;
		case 2:
			drop2 = new BulletPack();
			break;
		}
		drop1->SetPosition(this->GetPosition());
		drop1->heapReference = drop1;
		drop2->SetPosition(this->GetPosition());
		drop2->Move(15, 15);
		drop2->heapReference = drop2;
		Game::GetInstance()->activeLoots.push_back(drop1);
		Game::GetInstance()->activeLoots.push_back(drop2);
		break;
	}
	}

	// 3. Disable all active projectiles shot previously by the dead enemy
	if (Game::GetInstance()->activeProjectiles.size() != 0)
	{
		for (auto projectile : Game::GetInstance()->activeProjectiles)
		{
			if (projectile->heapReference == reinterpret_cast<Ammo*>(0xDDDDDDDD)) continue; // Deleted pointer
			if (projectile->GetSourceWeapon()->GetWeaponOwner() == this) projectile->Disable();
			if (Game::GetInstance()->activeProjectiles.size() == 1) break;
		}
	}

	// 4. Disable enemy object and await destroy.
	this->Disable();
}

// Decreases the entity's health by amount.
void Enemy::ReceiveDamage(int amount)
{
	this->health -= amount;

	if (this->health < 0)
		this->enemyState = EnemyState::Dead;
}

// Get reference to the entity's bow.
Weapon * Enemy::GetBowPointer()
{
	return bow;
}

// Removes the entity from the game and free heap memory.
void Enemy::Destroy()
{
	if (Game::GetInstance()->activeEnemies.size() == 0) return;

	if (Game::GetInstance()->activeEnemies.size() == 1)
	{
		Game::GetInstance()->activeEnemies.clear();
		delete heapReference;
	}
	else
	{
		list<Enemy*>::iterator iter = Game::GetInstance()->activeEnemies.begin();
		while (iter != Game::GetInstance()->activeEnemies.end())
		{
			if ((*iter)->uniqueEnemyId == this->uniqueEnemyId)
			{
				// Remove itself from active enemy list and free heap memory
				iter = Game::GetInstance()->activeEnemies.erase(iter);
				delete heapReference;
			}
			else
			{
				++iter;
			}
		}
	}
}