#ifdef OLC_PGEX_AnimatedSprite
#define OLC_PGEX_AnimatedSprite


namespace olc
{

	class AnimatedSprite : public olc::PGEX
	{
		
	public:
		int CurrFrame = 0;
		int SpriteXOffset = 0;
		// this is a class to draw an animated sprite - takes in 
		// a sprite
		// height and width of frame
		// number of frames
		// how long the frame should play in seconds
	private:
		float DeltaFrameTime = 0;
		int frames = 0;
		int SpriteWidth = 32;
		int SpriteHeight = 32;
		
		int SpriteYOffset = 0;
		
		float FrameTime = 0;
		bool pReverse = false;

		olc::Sprite* sprHolder;

		int SprScale = 1;
	

	public:
		AnimatedSprite(std::string ImageFile,int sprWidth, int SprHeight,int SprFrames, float SprFrameTime,bool reverse = false);
		//AnimatedSprite();
		void DrawSprite(int x,int  y, float dt);
			
		
	};
	     
}

namespace olc
{

	AnimatedSprite::AnimatedSprite(std::string ImageFile, int SprWidth, int SprHeight, int SprFrames, float SprFrameTime, bool reverse )
	{
		sprHolder = new olc::Sprite(ImageFile);
		frames = SprFrames - 1;
		SpriteWidth = SprWidth;
		SpriteHeight = SprHeight;
		FrameTime = SprFrameTime;
		pReverse = reverse;

		if (pReverse)
		{
			CurrFrame = frames;
			SpriteXOffset = SpriteWidth * (frames - 1);
		}

		
		



		

	};
	
	//AnimatedSprite::AnimatedSprite()
	//{
	//
	//}

	void AnimatedSprite::DrawSprite(int x, int y, float dt)

	{
		if (sprHolder == nullptr)
		{
			//something has gone wrong
			return;
		}

		if (!pReverse)
			//sprite animation should play back in normal order
		{

			//dt holds the felapsed time since last frame
			DeltaFrameTime += dt;
			if (DeltaFrameTime > FrameTime)
			{
				//we need to change Frame
				// reset the delta and check for next frame
				DeltaFrameTime = 0;
				if (CurrFrame < frames )
				{
					// we should increment the frame
					CurrFrame++;
					//change the offset of X
					SpriteXOffset = SpriteWidth * CurrFrame;
					

				}
				else
				{
					// we need to reset the frame count and the offset
					CurrFrame = 0;
					SpriteXOffset = 0;
				}

			}

		}
		else
			
		{
			// sprite should play back in reverse
			//dt holds the felapsed time since last frame
			DeltaFrameTime += dt;
			if (DeltaFrameTime > FrameTime)
			{
				//we need to change Frame
				// reset the delta and check for next frame
				DeltaFrameTime = 0;
				if (CurrFrame == 0   )
				{

					// we need to reset the frame count and the offset
					CurrFrame = frames;
					SpriteXOffset = SpriteWidth * (CurrFrame );
					// we will want to keep this last frame to draw in a second before resetting for next run through the logic

				
					

				}
				else
				{
					// we should decrement the frame

					SpriteXOffset = SpriteWidth * (CurrFrame - 1);
					CurrFrame--;
					//change the offset of X
					
				}

			}




		}

		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawPartialSprite(x, y,sprHolder, SpriteXOffset,SpriteYOffset,SpriteWidth,SpriteHeight,SprScale);
		pge->SetPixelMode(olc::Pixel::NORMAL);

	}
	


}
#endif
