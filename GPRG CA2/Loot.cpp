#include "stdafx.h"
#include "Loot.h"

Loot::Loot()
{
	// Generate unique id
	bool isUnique;
	do {
		isUnique = true;
		uniqueLootID = rand() % 1000 + 1; // 1 - 1000

		list<Loot*>::iterator iter = Game::GetInstance()->activeLoots.begin();
		while (iter != Game::GetInstance()->activeLoots.end() && !isUnique)
		{
			if ((*iter)->uniqueLootID == uniqueLootID)
			{
				isUnique = false;
				break;
			}
		}
	} while (!isUnique);

	lifeTime = 15.f;
}

void Loot::Update(float deltaTime)
{
	lifeTime -= deltaTime;
	if (lifeTime <= 0) Disable();
}

void Loot::Destroy()
{
	if (Game::GetInstance()->activeLoots.size() == 0) return;

	if (Game::GetInstance()->activeLoots.size() == 1)
	{
		Game::GetInstance()->activeLoots.clear();
		delete heapReference;
	}
	else
	{
		list<Loot*>::iterator iter = Game::GetInstance()->activeLoots.begin();
		while (iter != Game::GetInstance()->activeLoots.end())
		{
			if ((*iter)->uniqueLootID == this->uniqueLootID)
			{
				// Remove itself from active projectiles list and free heap memory
				iter = Game::GetInstance()->activeLoots.erase(iter);
				delete heapReference;
			}
			else
				++iter;
		}
	}
}