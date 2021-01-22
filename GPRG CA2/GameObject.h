#pragma once

class GameObject
{
public:
	GameObject();

	Texture texture; // The object's image texture
	Sprite sprite; // The object's drawable sprite

	bool isActive; // Is the object still active
	bool enableDraw; // Enable to draw to screen

	void LoadTextureAndSprite(Texture _texture);

	void SetPosition(float x, float y);
	void SetPosition(Vector2f location);
	void SetPosition(Vector2i location);
	void SetRotation(float angle);
	void SetOrigin(float x, float y);

	Vector2f GetPosition();
	float GetRotation();
	FloatRect GetCollider();

	void Move(Vector2f &vector);
	void Move(float x, float y);

	void Disable();
};