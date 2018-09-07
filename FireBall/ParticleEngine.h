#pragma once

#include "SDLTexture.h"
#include <vector>

class ParticleEngine 
{
public:


	ParticleEngine();
	~ParticleEngine();

	//Initialize position and animation
	ParticleEngine(int x, int y, SDLTexture gRedTexture, SDLTexture gGreenTexture, SDLTexture gBlueTexture);

	//Shows the particle
	void render(SDL_Renderer* gRenderer, SDLTexture gShimmerTexture);

	//Checks if particle is dead
	bool isDead();

	//Current frame of animation
	int mFrame;


private:
	//Offsets
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	
	//Type of particle
	SDLTexture *mTexture;



	SDLTexture mgRedTexture;
	SDLTexture mgGreenTexture;
	SDLTexture mgBlueTexture;
	SDLTexture mgShimmerTexture;
	

	
};

