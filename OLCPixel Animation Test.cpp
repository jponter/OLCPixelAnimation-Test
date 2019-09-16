#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
// Override base class with your custom functionality

#define OLC_PGEX_AnimatedSprite
#include "olcPGEX_AnimatedSprite.h"


olc::AnimatedSprite *sprPlayer;
olc::AnimatedSprite* sprPlayer2;
olc::AnimatedSprite* sprPlayer3;
olc::AnimatedSprite* sprPlayer4;

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Demo for olcPGEX_AnimatedSprite";
	}

private:
	



public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		sprPlayer = new olc::AnimatedSprite("idle_4.png",32,32,4,0.1f);
		sprPlayer2 = new olc::AnimatedSprite("walk right 6.png", 32, 32, 6, 0.1f);
		sprPlayer3 = new olc::AnimatedSprite("walk left 6.png", 32, 32, 6, 0.1f,true);
		sprPlayer4 = new olc::AnimatedSprite("jump 8.png", 32, 32, 8, 0.2f);

		
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame, draws random coloured pixels
		Clear(olc::BLACK);
		sprPlayer->DrawSprite((ScreenWidth()/2)-16, (ScreenHeight()/2)-16, fElapsedTime);
		sprPlayer2->DrawSprite((ScreenWidth() / 2) - 16-32, (ScreenHeight() / 2) - 16, fElapsedTime);
		sprPlayer3->DrawSprite((ScreenWidth() / 2) + 16 + 32, (ScreenHeight() / 2) - 16, fElapsedTime);
		sprPlayer4->DrawSprite((ScreenWidth() / 2) - 16, (ScreenHeight() / 2) + 16 + 32, fElapsedTime);

		//std::string sDebug1 = "Current Frame " + std::to_string(sprPlayer2->CurrFrame) + " X: Offset " + std::to_string(sprPlayer2->SpriteXOffset);
		
		//DrawString(0, 0, sDebug1, olc::WHITE);
		
		return true;
	}
};
int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}
