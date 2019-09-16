#ifdef OLC_PGEX_AnimatedSprite
#define OLC_PGEX_AnimatedSprite


namespace olc
{

	class AnimatedSprite : public olc::PGEX
	{
		
	public:
		int CurrFrame = 0; // someone might want to know the current frame
		
		// this is a class to draw an animated sprite - takes in 
		// a sprite
		// height and width of frame
		// number of frames
		// how long the frame should play in seconds
		// whether the animation should play in reverse
	private:
		float DeltaFrameTime = 0; //internal counter for time between elapsed frames
		int frames = 0; 
		int SpriteWidth = 32;
		int SpriteHeight = 32;
		int SpriteXOffset = 0;
		int SpriteYOffset = 0;
		
		float FrameTime = 0;
		bool pReverse = false;

		olc::Sprite* sprHolder; // space to store the actual sprite

		int SprScale = 1; //not used at the moment
	

	public:
		AnimatedSprite(std::string ImageFile,int sprWidth, int SprHeight,int SprFrames, float SprFrameTime,bool reverse = false);
		void DrawSprite(int x,int  y, float dt);
			
		
	};
	     
}

namespace olc
{

	AnimatedSprite::AnimatedSprite(std::string ImageFile, int SprWidth, int SprHeight, int SprFrames, float SprFrameTime, bool reverse )
	{
		sprHolder = new olc::Sprite(ImageFile); // use olc::Sprite to set the image name for our sprite tile set
		frames = SprFrames - 1; // internal logic this actual number of frames from 0..sprFrames-1 will = sprFrames
		SpriteWidth = SprWidth; // width in pixels
		SpriteHeight = SprHeight; // height in pixels
		FrameTime = SprFrameTime; // how long between frames of sprite in seconds 0.2f for example is quite nice
		pReverse = reverse; // set this if the animation should start at last frame and work back to first  - reverse default is false

		if (pReverse)
		{

			//set up the logic for a reverse sprite
			CurrFrame = frames;
			SpriteXOffset = SpriteWidth * (frames - 1);
		}	

	};
	
	

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
					

				
					

				}
				else
				{
					
					// we should decrement the frame
					SpriteXOffset = SpriteWidth * (CurrFrame - 1);
					// we should decrement the frame
					CurrFrame--;
					
					
				}

			}




		}


		//call our reference of pixelgame engine with a masked draw then reset the pixel draw mode
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawPartialSprite(x, y,sprHolder, SpriteXOffset,SpriteYOffset,SpriteWidth,SpriteHeight,SprScale);
		pge->SetPixelMode(olc::Pixel::NORMAL);

	}
	


}
#endif
