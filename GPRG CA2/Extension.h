#pragma once
class Extension
{
public:
	static float GetMagnitude(Vector2f vector);

	static void Normalize(Vector2f &vector);

	static bool CheckCollision(GameObject* gameobject1, GameObject* gameobject2);
};