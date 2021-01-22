#pragma once

// This class is a generic loot class that all lootable objects should inherit from.
class Loot : public GameObject
{
public:
	// Default constructor. This class is abstract and should be created with a derived class.
	Loot();

	int uniqueLootID;
	Loot * heapReference;

	Player * player = nullptr;

	float lifeTime;

	virtual void PickUp() = 0;

	void Update(float dt);
	void Destroy();
};

