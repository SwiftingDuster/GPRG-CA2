#include "stdafx.h"
#include "ResourceHolder.h"

 Font ResourceHolder::FontHolder::textFont;
 
 Texture ResourceHolder::MainMenuTextureHolder::buttonContainerFrameTexture;
 Texture ResourceHolder::MainMenuTextureHolder::tutorialContainerFrameTexture;
 Texture ResourceHolder::MainMenuTextureHolder::buttonFrameTexture;

 Texture ResourceHolder::TextureHolder::backgroundTexture;
 Texture ResourceHolder::TextureHolder::fountainTexture;

 Texture ResourceHolder::TextureHolder::playerTexture;
 Texture ResourceHolder::TextureHolder::enemyTexture;

 Texture ResourceHolder::TextureHolder::bowTexture;
 Texture ResourceHolder::TextureHolder::musketTexture;

 Texture ResourceHolder::TextureHolder::arrowTexture;
 Texture ResourceHolder::TextureHolder::bulletTexture;

 Texture ResourceHolder::TextureHolder::healthPackTexture;
 Texture ResourceHolder::TextureHolder::arrowPackTexture;
 Texture ResourceHolder::TextureHolder::bulletPackTexture;

 Texture ResourceHolder::TextureHolder::arrowIconTexture;
 Texture ResourceHolder::TextureHolder::bulletIconTexture;

 Texture ResourceHolder::TextureHolder::healthBarFrameTexture;
 Texture ResourceHolder::TextureHolder::livesFrameTexture;

 SoundBuffer ResourceHolder::AudioHolder::bowShootSound;
 SoundBuffer ResourceHolder::AudioHolder::musketShootSound;

void ResourceHolder::LoadResources()
{
	FontHolder::textFont.loadFromFile("Assets/Font/RobotoSlab-Regular.ttf");

	ResourceHolder::MainMenuTextureHolder::buttonContainerFrameTexture.loadFromFile("Assets/UI/MainMenu/Button_Container_Frame.png");
	ResourceHolder::MainMenuTextureHolder::tutorialContainerFrameTexture.loadFromFile("Assets/UI/MainMenu/Tutorial_Container_Frame.png");
	ResourceHolder::MainMenuTextureHolder::buttonFrameTexture.loadFromFile("Assets/UI/MainMenu/Button_Frame.png");

	TextureHolder::backgroundTexture.loadFromFile("Assets/Environment/Dirt.png");
	TextureHolder::fountainTexture.loadFromFile("Assets/Environment/Fountain.png");

	TextureHolder::playerTexture.loadFromFile("Assets/Characters/Player.png");
	TextureHolder::enemyTexture.loadFromFile("Assets/Characters/Enemy.png");

	TextureHolder::bowTexture.loadFromFile("Assets/Weapons/Weapon_Bow.png");
	TextureHolder::musketTexture.loadFromFile("Assets/Weapons/Weapon_Musket.png");

	TextureHolder::arrowTexture.loadFromFile("Assets/Weapons/Projectile_Bow_Arrow.png");
	TextureHolder::bulletTexture.loadFromFile("Assets/Weapons/Projectile_Musket_Bullet.png");

	TextureHolder::healthPackTexture.loadFromFile("Assets/PickUps/Health_Pack.png");
	TextureHolder::arrowPackTexture.loadFromFile("Assets/PickUps/Arrow_Pack.png");
	TextureHolder::bulletPackTexture.loadFromFile("Assets/PickUps/Bullet_Pack.png");

	TextureHolder::arrowIconTexture.loadFromFile("Assets/UI/Icon_Weapon_Bow_Arrow.png");
	TextureHolder::bulletIconTexture.loadFromFile("Assets/UI/Icon_Weapon_Musket_Bullet.png");

	TextureHolder::healthBarFrameTexture.loadFromFile("Assets/UI/Healthbar_Frame.png");
	TextureHolder::livesFrameTexture.loadFromFile("Assets/UI/Lives_Frame.png");

	AudioHolder::bowShootSound.loadFromFile("Assets/Sounds/Bow_Fire-StephanSchutze.wav");
	AudioHolder::musketShootSound.loadFromFile("Assets/Sounds/Sniper_Shot-Liam.wav");
}