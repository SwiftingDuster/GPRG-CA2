#include "stdafx.h"
#include <cstdlib>
#include "Game.h"

#pragma region Constructor, Setup and Run
// Reference to itself
Game * Game::Instance;

// Constructor to create a new game.
Game::Game(int sizeX, int sizeY, String title) :window(VideoMode(sizeX, sizeY), title)
{
	Instance = this;
}

// Delete all objects allocated on the heap before exiting.
Game::~Game()
{
	for (auto projectile : activeProjectiles)
	{
		delete projectile->heapReference;
	}
	for (auto enemy : activeEnemies)
	{
		delete enemy->heapReference;
	}
	for (auto loot : activeLoots)
	{
		delete loot->heapReference;
	}
}

// Set up resources for the game
void Game::Setup()
{
	// Cap to 60FPS #PCMasterRace
	window.setFramerateLimit(60);

#pragma region Setting Up Game Resources and UI
	// Font, background and fountain
	font = ResourceHolder::FontHolder::textFont;
	dirtBackgroundPtr->LoadTextureAndSprite(ResourceHolder::TextureHolder::backgroundTexture);
	fountainLeftPtr->LoadTextureAndSprite(ResourceHolder::TextureHolder::fountainTexture);
	fountainRightPtr->LoadTextureAndSprite(ResourceHolder::TextureHolder::fountainTexture);
	fountainLeftPtr->SetOrigin(39, 39);
	fountainRightPtr->SetOrigin(40, 39);
	fountainLeftPtr->SetPosition(WindowSizeX / 4, WindowSizeY / 2);
	fountainRightPtr->SetPosition(WindowSizeX / 4 * 3, WindowSizeY / 2);
	
	// Main Menu UI
	menuButtonContainerFrame.LoadTextureAndSprite(ResourceHolder::MainMenuTextureHolder::buttonContainerFrameTexture);
	menuButtonContainerFrame.SetPosition(300, 100);

	menuTutorialContainerFrame.LoadTextureAndSprite(ResourceHolder::MainMenuTextureHolder::tutorialContainerFrameTexture);
	menuTutorialContainerFrame.SetPosition(40, 550);

	menuStartButtonFrame.LoadTextureAndSprite(ResourceHolder::MainMenuTextureHolder::buttonFrameTexture);
	menuStartButtonFrame.SetPosition(WindowSizeX / 2 - menuStartButtonFrame.sprite.getGlobalBounds().width / 2, WindowSizeY / 2 - 80);

	menuQuitButtonFrame.LoadTextureAndSprite(ResourceHolder::MainMenuTextureHolder::buttonFrameTexture);
	menuQuitButtonFrame.SetPosition(WindowSizeX / 2 - menuQuitButtonFrame.sprite.getGlobalBounds().width / 2, WindowSizeY / 2);
	
	titleButtonText.setFont(font);
	titleButtonText.setCharacterSize(60);
	titleButtonText.setString("Medieval Defender");
	titleButtonText.setPosition(375, WindowSizeY / 2 - 200);
	titleButtonText.setFillColor(Color::Red);

	startButtonText.setFont(font);
	startButtonText.setString("Start");
	startButtonText.setPosition(menuStartButtonFrame.GetPosition().x + 110, menuStartButtonFrame.GetPosition().y + 5);
	startButtonText.setFillColor(Color::Black);

	quitButtonText.setFont(font);
	quitButtonText.setString("Quit");
	quitButtonText.setPosition(menuQuitButtonFrame.GetPosition().x + 115, menuQuitButtonFrame.GetPosition().y + 5);
	quitButtonText.setFillColor(Color::Black);

	tutorialText.setFont(font);
	tutorialText.setCharacterSize(24);
	tutorialText.setString("How to play: \n\nUse WSAD to move, Mouse to Aim, Num1/Num2 to change weapons and Left Mouse Button to Shoot.\nEscape to Pause game.");
	tutorialText.setPosition(WindowSizeX / 2 - tutorialText.getGlobalBounds().width / 2, WindowSizeY / 2 + 200);
	tutorialText.setFillColor(Color::Black);

	// Game UI
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setPosition(WindowSizeX / 2 - 100, 20);
	scoreText.setString("Score: 0");
	scoreText.setFillColor(Color::White);
	
	healthBarFrame.LoadTextureAndSprite(ResourceHolder::TextureHolder::healthBarFrameTexture);
	healthBarFrame.SetPosition(30, 20);
	healthBar.setPosition(healthBarFrame.GetPosition().x + 6, healthBarFrame.GetPosition().y + 6);
	healthBar.setSize(Vector2f((float)HealthBarSizeX, (float)HealthBarSizeY));
	healthBar.setFillColor(Color::Green);

	livesFrame.LoadTextureAndSprite(ResourceHolder::TextureHolder::livesFrameTexture);
	livesFrame.SetPosition(30, 70);

	livesText.setFont(font);
	livesText.setPosition(55, 70);
	livesText.setFillColor(Color::Red);

	arrowsRemainingText.setFont(font);
	arrowsRemainingText.setPosition(1200, 15);
	arrowsRemainingText.setString(to_string(Player::MaxArrowAmmo));
	arrowsRemainingText.setFillColor(Color::Green);

	bulletRemainingText.setFont(font);
	bulletRemainingText.setPosition(1200, 75);
	bulletRemainingText.setString(to_string(Player::MaxMusketAmmo));
	bulletRemainingText.setFillColor(Color::Red);

	gamePausedText.setFont(font);
	gamePausedText.setCharacterSize(40);
	gamePausedText.setString("Paused");
	gamePausedText.setPosition(580, 360);
	gamePausedText.setFillColor(Color::Red);
	gamePausedText.setStyle(Text::Underlined);

	// End of Game UI
	gameOverContainerFrame.LoadTextureAndSprite(ResourceHolder::MainMenuTextureHolder::buttonContainerFrameTexture);
	gameOverContainerFrame.SetPosition(WindowSizeX / 2 - gameOverContainerFrame.sprite.getGlobalBounds().width / 2, WindowSizeY / 2 - 200);
	
	gameOverMainMenuButtonFrame.LoadTextureAndSprite(ResourceHolder::MainMenuTextureHolder::buttonFrameTexture);
	gameOverMainMenuButtonFrame.SetPosition(WindowSizeX / 2 - gameOverMainMenuButtonFrame.sprite.getGlobalBounds().width / 2, WindowSizeY / 2 + 100);

	gameOverMainMenuButtonText.setFont(font);
	gameOverMainMenuButtonText.setPosition(gameOverMainMenuButtonFrame.GetPosition().x + 70, gameOverMainMenuButtonFrame.GetPosition().y + 5);
	gameOverMainMenuButtonText.setString("Main Menu");
	gameOverMainMenuButtonText.setFillColor(Color::Blue);
	
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(50);
	gameOverText.setString("Game Over");
	gameOverText.setFillColor(Color::Blue);
	gameOverText.setPosition(WindowSizeX / 2 - 100, WindowSizeY / 2 - 50);
	
	arrowIcon.LoadTextureAndSprite(ResourceHolder::TextureHolder::arrowIconTexture);
	arrowIcon.SetPosition(1130, 10);
	arrowIcon.sprite.setScale(5, 5);

	bulletIcon.LoadTextureAndSprite(ResourceHolder::TextureHolder::bulletIconTexture);
	bulletIcon.SetPosition(1130, 70);
	bulletIcon.sprite.setScale(5, 5);

	// Sounds
	bowShootSound.setBuffer(ResourceHolder::AudioHolder::bowShootSound);
	musketShootSound.setBuffer(ResourceHolder::AudioHolder::musketShootSound);
#pragma endregion

	// Game processing
	player.GetBowPointer()->SetAsPlayerWeapon();
	player.GetMusketPointer()->SetAsPlayerWeapon();
	score = 0;
}

// Runs the game
void Game::Run()
{
	while (!gameRunning)
	{
		MenuProcessEvents();
		MenuRender();
	}
	while (window.isOpen() && gameRunning)
	{
		ProcessEvents();
		if (!gamePaused)
		{
			Update();
			PostUpdate();
		}
		Render();
	}
}

#pragma endregion

#pragma region Main Menu Loop
// Process events for the main menu
void Game::MenuProcessEvents()
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			exit(0);
	}
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		if (menuStartButtonFrame.GetCollider().contains(Vector2f(mousePosition)))
		{
			totalGameTimeClock.restart();
			gameRunning = true;
		}
		else if (menuQuitButtonFrame.GetCollider().contains(Vector2f(mousePosition)))
		{
			exit(0);
		}
	}
}

// Render graphics for the main menu
void Game::MenuRender()
{
	window.clear();
	window.draw(dirtBackground.sprite);
	window.draw(menuButtonContainerFrame.sprite);
	window.draw(menuTutorialContainerFrame.sprite);
	window.draw(menuStartButtonFrame.sprite);
	window.draw(menuQuitButtonFrame.sprite);
	window.draw(titleButtonText);
	window.draw(startButtonText);
	window.draw(quitButtonText);
	window.draw(tutorialText);
#if DEBUG
	// ShowCursorCoordinates();
#endif
	window.display();
}

#pragma endregion

#pragma region Game Loop Generic
// Process game input and events
void Game::ProcessEvents()
{
#pragma region Game Over Processing
	if (gameOver) // Only check for main menu button click and return if gameover.
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			Vector2i mousePosition = Mouse::getPosition(window);
			if (gameOverMainMenuButtonFrame.GetCollider().contains(Vector2f(mousePosition)))
			{
				// Player started a new game after ending a game. Reset everything.
				player.SetPosition(WindowSizeX / 2, WindowSizeY / 2);
				player.SetHealth(100);
				player.RestoreArrows(player.MaxArrowAmmo);
				player.RestoreBullets(player.MaxMusketAmmo);
				for (auto projectile : activeProjectiles)
				{
					delete projectile->heapReference;
				}
				for (auto enemy : activeEnemies)
				{
					delete enemy->heapReference;
				}
				for (auto loot : activeLoots)
				{
					delete loot->heapReference;
				}
				activeProjectiles.clear();
				activeEnemies.clear();
				activeLoots.clear();
				scoreText.setPosition(WindowSizeX / 2 - 100, 20);
				scoreText.setFillColor(Color::White);
				gamePaused = gameOver = false;
				gameRunning = false;
				Run();
			}
		}
		return;
	}
#pragma endregion

#pragma region Timer and Clock
	// Get time taken to render last frame
	deltaTime = clock.restart().asSeconds();
	// Get time since game started.
	timeSinceGameStart = totalGameTimeClock.getElapsedTime().asSeconds() - totalGamePauseTime;
	if (gamePaused) totalGamePauseTime += deltaTime;
#pragma endregion

#pragma region Random Number Generator Seed Initialization
	// Generate a new seed for rand() every second.
	if (timeSinceLastSecond <= 0)
	{
		srand((unsigned int)time(NULL));
		timeSinceLastSecond = 1;
	}
	else
	{
		timeSinceLastSecond -= deltaTime;
	}

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			exit(0);
		if (event.type == Event::LostFocus)
			gamePaused = true;
	}
#pragma endregion

#pragma region Pause Toggle
	if (Keyboard::isKeyPressed(Keyboard::Escape) && timeSinceLastPause > 1.f)
	{
		gamePaused = !gamePaused;
	}
	else
	{
		timeSinceLastPause += deltaTime;
	}
#pragma endregion

	if (!gamePaused) // Game Input Events
	{
#pragma region Player Movement Keys
		// See UpdatePlayer() for implementation.
		leftKeyDown = Keyboard::isKeyPressed(Keyboard::A);
		rightKeyDown = Keyboard::isKeyPressed(Keyboard::D);
		upKeyDown = Keyboard::isKeyPressed(Keyboard::W);
		downKeyDown = Keyboard::isKeyPressed(Keyboard::S);
#pragma endregion

#pragma region Weapon Use
		attackKeyDown = Mouse::isButtonPressed(Mouse::Button::Left);
		if (timeSinceGameStart < 0.5f) attackKeyDown = false; // Prevent IsButtonPressed for LMB triggering during main menu to game transition causing a random shot from the bow
#pragma endregion

#pragma region Weapon Swap
		weapon1KeyDown = Keyboard::isKeyPressed(Keyboard::Num1);
		weapon2KeyDown = Keyboard::isKeyPressed(Keyboard::Num2);
#pragma endregion
	}
}

// Update gameobjects
void Game::Update()
{
	UpdatePlayer();
	UpdateProjectiles();
	UpdateEnemies();
	UpdateLoots();
	UpdateUIOverlay();
}

// Collision checks and collision response
void Game::PostUpdate()
{
	CheckCollisions();
}

// Rendering of graphics based on gameobject's state
void Game::Render()
{
	window.clear();

	RenderConstantObjectQueue();
	RenderProjectiles();
	RenderEnemies();
	RenderLoots();
	RenderUIOverlay();

#if DEBUG
	ShowCursorCoordinates();
#endif

	window.display();
}

#pragma endregion

#pragma region Game Loop Individual Methods

#pragma region Update

// Updating of player: Movement, Weapon Swap, Weapon Use, Weapon Follow, Weapon Use Cooldown
void Game::UpdatePlayer()
{
	if (player.GetHealth() <= 0) // Check if player is dead
	{
		player.SetHealth(0);
		player.Die();
	}

#pragma region Movement and Look Direction
	// Pass the mouse pointer's position to the player class to be used for weapon shooting
	Game::GetInstance()->GetPlayer()->SetMousePosition(Mouse::getPosition(window));

	// Process movement from input
	float movementX = 0, movementY = 0;
	if (leftKeyDown) {
		movementX -= 1;
	}
	if (rightKeyDown) {
		movementX += 1;
	}
	if (upKeyDown) {
		movementY -= 1;
	}
	if (downKeyDown) {
		movementY += 1;
	}

	// Check screen border collision
	Vector2f desiredLocation(player.GetPosition().x + (movementX * playerSpeed * deltaTime), player.GetPosition().y + (movementY * playerSpeed * deltaTime));
	if (desiredLocation.x > WindowSizeX - 20 || desiredLocation.x < 0 + 20 || // Is the player out of screen area if move is called?
		desiredLocation.y > WindowSizeY - 20 || desiredLocation.y < 0 + 20)
	{
		// Dont do anything since it will collide if player moves toward that direction
	}
	else // It's ok to move to the desiredLocation.
	{
		player.lastMovement = Vector2f(movementX * playerSpeed * deltaTime, movementY * playerSpeed * deltaTime);
		player.Move(player.lastMovement);
	}

	// Rotates player and held objects towards mouse cursor.
	float angleToMouse = (atan2(Mouse::getPosition(window).y - player.GetPosition().y, Mouse::getPosition(window).x - player.GetPosition().x) * 180.f) / 3.141f;
	player.SetRotation(angleToMouse);
	bowGOPtr->SetRotation(angleToMouse - 45);
	musketGOPtr->SetRotation(angleToMouse);

#pragma endregion

#pragma region Weapon Use
	if (attackKeyDown) player.Attack(); // Process attack input
#pragma endregion

#pragma region Weapon Swap
	// Process weapon change input
	if (weapon1KeyDown) {
		player.EquipWeapon(player.GetBowPointer());
		player.GetBowPointer()->SetAttackPower(35);
		bowGOPtr->enableDraw = true;
		musketGOPtr->enableDraw = false;
		arrowsRemainingText.setFillColor(Color::Green);
		bulletRemainingText.setFillColor(Color::Red);
	}
	else if (weapon2KeyDown) 
	{
		player.EquipWeapon(player.GetMusketPointer());
		player.GetMusketPointer()->SetAttackPower(80);
		bowGOPtr->enableDraw = false;
		musketGOPtr->enableDraw = true;
		arrowsRemainingText.setFillColor(Color::Red);
		bulletRemainingText.setFillColor(Color::Green);
	}
#pragma endregion

#pragma region Weapon Follow Player and Weapon Cooldown
	// Make bow and musket follow the player.
	bowGOPtr->SetPosition((playerGOPtr->sprite).getPosition());
	musketGOPtr->SetPosition((playerGOPtr->sprite).getPosition());

	// Reduce the weapon cooldown by deltatime.
	player.GetBowPointer()->Cooldown(deltaTime);
	player.GetMusketPointer()->Cooldown(deltaTime);
#pragma endregion
}

// Updating of projectiles: Location, Collision and Disabling if out of screen.
void Game::UpdateProjectiles()
{
	for (auto projectile : activeProjectiles) // Loop through active projectiles
	{
		Vector2f projectileLocation = projectile->GetPosition();
		float x = projectileLocation.x;
		float y = projectileLocation.y;
		if (x > WindowSizeX || x < 0 || // Is the Projectile out of screen area?
			y > WindowSizeY || y < 0)
		{
			projectile->Disable(); // Disable from render queue and await destroy
		}
		else // Projectile is within screen, so move it forward.
		{
			projectile->Update(deltaTime);
		}
	}
}

// Updating of enemies: Auto Spawning, FSM Controlled Actions.
void Game::UpdateEnemies()
{
	// Get time since last enemy spawn
	timeSinceLastEnemySpawn += deltaTime;
	// Cooldown is dynamic. The longer the game, the faster enemies spawn.
	// Linear decrease in Y. [Graph: y = -0.005x + 3] 
	// [y = Cooldown, x = Time since Game Start]
	// [x = 600 when y = 0] & [x = 0 when y = 3]
	// Spawn speed starts at 0.333enemy/s, then increases gradually until there is no cooldown 10 mins into the game.
	// [How To Get Rekt] 10 Minute Mark: Spawn Rate = Framerate [60FPS Cap]
	if (timeSinceGameStart > 600) timeSinceGameStart = 600; // If x is more than 600 the spawn time will be negative.
	float spawnCooldown = -0.005f * timeSinceGameStart + 3;  // Calculate cooldown using the above formula
	if (gameRunning && activeEnemies.size() < 10 && timeSinceLastEnemySpawn >= spawnCooldown)
	{
		timeSinceLastEnemySpawn = 0;
		Enemy * enemy = new Enemy();
		enemy->heapReference = enemy;
		activeEnemies.push_back(enemy);
	}
	for (auto enemy : activeEnemies)
	{
		enemy->Update(deltaTime, enemySpeed);
		enemy->GetBowPointer()->SetPosition(enemy->GetPosition());
		enemy->GetBowPointer()->SetRotation(enemy->GetRotation() - 45);
		enemy->GetBowPointer()->Cooldown(deltaTime);
	}
}

// Updating of loots: Check Player Pickup
void Game::UpdateLoots()
{
	// Loop through all active loots in the game and detect if player collected it
	for (auto loot : activeLoots)
	{
		loot->Update(deltaTime);
	}
}

// Updating of game UI: Score, Health, Lives, Arrow Count, Bullet Count
void Game::UpdateUIOverlay()
{
	// Update UI values to show updated data.
	scoreText.setString("Score: " + to_string(score));
	livesText.setString(to_string(player.GetLives()));
	arrowsRemainingText.setString(to_string(player.GetArrowsRemaining()));
	bulletRemainingText.setString(to_string(player.GetBulletsRemaining()));
	healthBar.setSize(Vector2f((float)HealthBarSizeX * ((float)player.GetHealth() / (float)player.MaxHealth), (float)HealthBarSizeY));
}

#pragma endregion

#pragma region Collision

// Checks game collision and provide collision response.
void Game::CheckCollisions()
{
	GameObject * fountains[2] = { gameObjects[1], gameObjects[2]};
	
	// Check entity collision against fountains
	for (auto fountain : fountains) // Loop fountains objects
	{
		if (Extension::CheckCollision(playerGOPtr, fountain)) // Is there collision?
		{
			player.Move(-player.lastMovement);
		}
		for (auto enemy : activeEnemies)
		{
			if (Extension::CheckCollision(enemy, fountain)) // Is there collision?
			{
				enemy->Move(-enemy->lastMovement);
			}
		}
	}

	// Check enemy collision with player and other enemies
	for (auto enemy : activeEnemies)
	{
		if (Extension::CheckCollision(playerGOPtr, enemy))
		{
			player.Move(-(player.lastMovement));
		}
		for (auto otherEnemy : activeEnemies)
		{
			if (enemy == otherEnemy) continue; // Don't check against itself.

			if (Extension::CheckCollision(enemy, otherEnemy))
			{
				enemy->Move(-(enemy->lastMovement));
			}
		}
	}

	// Check projectile collision against player, enemies and fountains
	if (activeProjectiles.size() != 0)
	{
		for (auto projectile : activeProjectiles)
		{
			// The current projectile is no longer active, therefore skip it.
			if (!projectile->isActive) continue;

			// Check one projectile against all enemies
			for (auto enemy : activeEnemies)
			{
				if (Extension::CheckCollision(projectile, enemy)) // Is there collision?
				{
					if (projectile->GetSourceWeapon()->GetIsPlayerWeapon()) // Collided. Is the arrow from the player?
					{
						enemy->ReceiveDamage(projectile->damage); // Arrow shot by player. Therefore damage the enemy.
						projectile->Disable(); // Arrow has hit target and is gone.
					}
				}
			}

			// Check one projectile against player
			if (Extension::CheckCollision(projectile, playerGOPtr)) // Is there collision?
			{
				if (!projectile->GetSourceWeapon()->GetIsPlayerWeapon()) // Collided. Is the arrow from the enemy?
				{
					player.ReceiveDamage(projectile->damage); // Arrow shot by enemy. Therefore damage the player.
					projectile->Disable(); // Arrow has hit target and is gone.
				}
			}

			// Projectile collision against fountains
			for (auto fountain : fountains) // Loop fountains objects
			{
				if (Extension::CheckCollision(projectile, fountain)) // Is there collision?
				{
					projectile->Disable(); // Arrow has hit fountain and is gone.
				}
			}
		}
	}

	// Check lootable items collision with player
	for (auto loot : activeLoots)
	{
		if (loot->GetCollider().intersects(player.GetCollider()))
		{
			loot->PickUp();
		}
	}
}

#pragma endregion

#pragma region Render

// Rendering of constant gameobjects: Background, Player, Player Weapons. (Never removed from the game)
void Game::RenderConstantObjectQueue()
{
	// Single object render queue 
	// There will be only one of each object each in the game and will never change.
	int index = 0;
	for (auto go : gameObjects)
	{
		if (gameObjects[index]->enableDraw) window.draw(gameObjects[index]->sprite); // Draw
		index++;
	}
}

// Rendering of projectiles: Arrows, Bullets
void Game::RenderProjectiles()
{
	if (activeProjectiles.size() != 0)
	{
		for (auto projectile : activeProjectiles) // Loop through active projectiles awaiting render or destroy
		{
			if (projectile->isActive) // Projectile is still within screen area
			{
				if (projectile->enableDraw) window.draw(projectile->sprite); // Is draw enabled? If so render it to screen.
			}
			else
			{
				if (projectile->heapReference != reinterpret_cast<Ammo*>(0xDDDDDDDD)) projectile->Destroy();
				break;
			}
		}
	}
}

// Rendering of enemies: New location
void Game::RenderEnemies()
{
	if (activeEnemies.size() != 0)
	{
		for (auto enemy : activeEnemies)
		{
			if (enemy->isActive) // Projectile is still within screen area
			{
				if (enemy->enableDraw) window.draw(enemy->sprite); // Is draw enabled? If so render it to screen.
				if (enemy->GetBowPointer()->enableDraw) window.draw(enemy->GetBowPointer()->sprite);
			}
			else
			{
				enemy->Destroy();
				break;
			}
		}
	}
}

// Rendering of loots: Timer countdown disable
void Game::RenderLoots()
{
	if (activeLoots.size() != 0)
	{
		for (auto loot : activeLoots)
		{
			if (loot->isActive)
			{
				if (loot->enableDraw) window.draw(loot->sprite);
			}
			else
			{
				loot->Destroy();
				break;
			}
		}
	}
}

// Rendering of Game UI: Score, Ammo Count, Health, Lives, Text/Windows
void Game::RenderUIOverlay()
{
	// Draw the UI overlay
	window.draw(arrowIcon.sprite);
	window.draw(bulletIcon.sprite);
	window.draw(arrowsRemainingText);
	window.draw(bulletRemainingText);
	window.draw(healthBarFrame.sprite);
	window.draw(healthBar);
	window.draw(livesFrame.sprite);
	window.draw(livesText);
	if (gamePaused && !gameOver) window.draw(gamePausedText);
	if (gameOver)
	{
		window.draw(gameOverContainerFrame.sprite);
		window.draw(gameOverMainMenuButtonFrame.sprite);
		window.draw(gameOverMainMenuButtonText);
		window.draw(gameOverText);
	}
	window.draw(scoreText);
}

#pragma endregion

#pragma endregion

#pragma region Public API

// End the game and show game over screen
void Game::GameOver()
{
	gamePaused = true;
	gameOver = true;
	scoreText.setPosition(gameOverContainerFrame.GetPosition().x + 250, gameOverContainerFrame.GetPosition().y + 30);
	scoreText.setFillColor(Color::Red);
}

// Get reference to the game
Game* Game::GetInstance()
{
	return Instance;
}

// Get reference to the player object
Player * Game::GetPlayer()
{
	return &player;
}

// Get whether game is running (Gameplay)
bool Game::GetGameRunning()
{
	return gameRunning;
}

// Increase score by a pre-calculated amount. This amount increases with game time.
void Game::IncreaseScore()
{
	this->score += (int)ceil(10 + timeSinceGameStart * 1.1);
}

// Play bow shooting sound
void Game::PlayBowShootSound()
{
	this->bowShootSound.play();
}

// Play musket shooting sound
void Game::PlayMusketShootSound()
{
	this->musketShootSound.play();
}
#pragma endregion

#pragma region Development
// For Development Visualization: 
// Show coordinates of mouse cursor in game. (Relative to game window)
// Place this method before a window.display() call.
void Game::ShowCursorCoordinates()
{
	Text coord;
	coord.setFont(font);
	coord.setCharacterSize(20);
	coord.setFillColor(Color::Green);
	coord.setPosition((float)Mouse::getPosition(window).x + 10, (float)Mouse::getPosition(window).y);
	coord.setString("X: " + to_string((int)coord.getPosition().x) + " Y: " + to_string((int)coord.getPosition().y));
	window.draw(coord);
}
#pragma endregion