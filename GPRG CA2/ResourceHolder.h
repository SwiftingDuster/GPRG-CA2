#pragma once

class ResourceHolder
{
public:
	struct FontHolder
	{
		static Font textFont;
	};

	struct MainMenuTextureHolder
	{
		static Texture buttonContainerFrameTexture;
		static Texture tutorialContainerFrameTexture;
		static Texture buttonFrameTexture;
	};

	struct TextureHolder
	{
		static Texture backgroundTexture;
		static Texture fountainTexture;

		static Texture playerTexture;
		static Texture enemyTexture;

		static Texture bowTexture;
		static Texture musketTexture;

		static Texture arrowTexture;
		static Texture bulletTexture;

		static Texture healthPackTexture;
		static Texture arrowPackTexture;
		static Texture bulletPackTexture;

		static Texture arrowIconTexture;
		static Texture bulletIconTexture;

		static Texture healthBarFrameTexture;
		static Texture livesFrameTexture;
	};

	struct AudioHolder
	{
		static SoundBuffer bowShootSound;
		static SoundBuffer musketShootSound;
	};

	static void LoadResources();
};