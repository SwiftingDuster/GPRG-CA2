#pragma once
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "Loot.h"
#include "GameObject.h"

class Game
{
public:
	const static int WindowSizeX = 1280, WindowSizeY = 768;
	const static int HealthBarSizeX = 198, HealthBarSizeY = 28;

	Game(int sizeX, int sizeY, String title);
	~Game();

	// This list contains reference to projectile objects on the heap. Delete is called in destructor.
	list<Ammo*> activeProjectiles;
	// This list contains reference to enemy objects on the heap. Delete is called in destructor.
	list<Enemy*> activeEnemies;
	// This list contains reference to lootable objects on the heap. Delete is called in destructor.
	list<Loot*> activeLoots;

	Vector2i enemySpawnPoints[6] =
	{
		Vector2i(0, 0), 
		Vector2i(WindowSizeX/2, 0), 
		Vector2i(WindowSizeX, 0), 
		Vector2i(0, WindowSizeY),
		Vector2i(WindowSizeX/2, WindowSizeY),
		Vector2i(WindowSizeX, WindowSizeY) 
	};

	void GameOver();

	static Game* GetInstance();
	Player* GetPlayer();
	bool GetGameRunning();

	void Setup();
	void Run();

	void IncreaseScore();
	void PlayBowShootSound();
	void PlayMusketShootSound();

	// Show coordinates of mouse cursor in game. (Relative to game window)
	void ShowCursorCoordinates(); 
private:
	static Game * Instance;

	RenderWindow window;
	Event event;
	Clock totalGameTimeClock;
	Clock clock;
	float deltaTime;

	float totalGamePauseTime = 0;
	float timeSinceGameStart = 0;
	float timeSinceLastSecond = 0;
	float timeSinceLastPause = 0;
	float timeSinceLastEnemySpawn = 0;

	bool leftKeyDown, rightKeyDown, upKeyDown, downKeyDown,
		attackKeyDown, weapon1KeyDown, weapon2KeyDown;

	unsigned int score;
	bool gameRunning = false;
	bool gamePaused = false;
	bool gameOver = false;

    float playerSpeed = 300;
	float enemySpeed = 100;

	Font font;

	// Main menu
	GameObject menuButtonContainerFrame;
	GameObject menuTutorialContainerFrame;
	GameObject menuStartButtonFrame;
	GameObject menuQuitButtonFrame;
	Text titleButtonText;
	Text startButtonText;
	Text quitButtonText;
	Text tutorialText;

	// In game UI
	GameObject healthBarFrame;
	RectangleShape healthBar;
	GameObject livesFrame;
	GameObject arrowIcon;
	GameObject bulletIcon;
	Text scoreText;
	Text livesText;
	Text arrowsRemainingText;
	Text bulletRemainingText;

	// End game UI
	GameObject gameOverContainerFrame;
	GameObject gameOverMainMenuButtonFrame;
	Text gamePausedText;
	Text gameOverText;
	Text gameOverMainMenuButtonText;

	// Sounds
	Sound bowShootSound;
	Sound musketShootSound;

	// Active gameobjects
	GameObject dirtBackground;
	GameObject fountainLeft, fountainRight;
	Player player;

	GameObject * dirtBackgroundPtr = &dirtBackground;
	GameObject * fountainLeftPtr = &fountainLeft;
	GameObject * fountainRightPtr = &fountainRight;
	GameObject * playerGOPtr = &player;
	GameObject * bowGOPtr = player.GetBowPointer();
	GameObject * musketGOPtr = player.GetMusketPointer();

	GameObject * gameObjects[6] =
	{
		dirtBackgroundPtr,
		fountainLeftPtr,
		fountainRightPtr,
		playerGOPtr,
		bowGOPtr,
		musketGOPtr,
	};

	void MenuProcessEvents();
	void MenuRender();

	void ProcessEvents();
	void Update();
	void PostUpdate();
	void Render();

	void UpdatePlayer();
	void UpdateProjectiles();
	void UpdateEnemies();
	void UpdateLoots();
	void UpdateUIOverlay();

	void CheckCollisions();

	void RenderConstantObjectQueue();
	void RenderProjectiles();
	void RenderEnemies();
	void RenderLoots();
	void RenderUIOverlay();
};

