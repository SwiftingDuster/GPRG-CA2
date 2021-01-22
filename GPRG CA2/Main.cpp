#include "stdafx.h"

int main()
{
	ResourceHolder::LoadResources();
	Game game(Game::WindowSizeX, Game::WindowSizeY, "Medieval Defender");
	game.Setup();
	game.Run();
	return 0;
}