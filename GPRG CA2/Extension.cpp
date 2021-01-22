#include "stdafx.h"
#include "Extension.h"

// Get the length(magnitude) of a vector.
float Extension::GetMagnitude(Vector2f vector)
{
	return sqrt((vector.x*vector.x) + (vector.y*vector.y));
}

// Normalize the vector that is passed into this method.
void Extension::Normalize(Vector2f &vector) // Vector passed by reference
{
	float magnitude = GetMagnitude(vector);
	vector = Vector2f(vector.x / magnitude, vector.y / magnitude);
}

// Checks whether two object is colliding.
bool Extension::CheckCollision(GameObject* gameobject1, GameObject* gameobject2)
{
	return gameobject1->GetCollider().intersects(gameobject2->GetCollider());
}