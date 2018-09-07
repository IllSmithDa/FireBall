#include "ParticleEngine.h"



ParticleEngine::ParticleEngine()
{
}


ParticleEngine::~ParticleEngine()
{
}




ParticleEngine::ParticleEngine(int x, int y, SDLTexture gRedTexture, SDLTexture gGreenTexture, SDLTexture gBlueTexture)
{
	mgRedTexture = gRedTexture;
	mgGreenTexture = gGreenTexture; 
	mgBlueTexture = gBlueTexture;

	//Set offsets
	mPosX = x - 5 + (rand() % 25);
	mPosY = y - 5 + (rand() % 25);

	//Initialize animation
	mFrame = rand() % 5;

	//Set type
	switch (rand() % 3)
	{
	case 0: mTexture = &mgRedTexture; 
		break;
	case 1: mTexture = &mgGreenTexture;
		break;
	case 2: mTexture = &mgBlueTexture; 
		break;
	}
}



void ParticleEngine::render(SDL_Renderer* gRenderer, SDLTexture gShimmerTexture)
{
	
	mgShimmerTexture = gShimmerTexture;
	//Show image


	//msprite.showImage(gRenderer);
	mTexture->renderWithAngle(mPosX, mPosY, gRenderer, NULL, SDL_FLIP_NONE);

	//Show shimmer
	if (mFrame % 2 == 0)
	{
		mgShimmerTexture.renderWithAngle(mPosX, mPosY, gRenderer, NULL, SDL_FLIP_NONE);
		//msprite.showShimmerTexture(gRenderer);
	}

	//Animate
	mFrame++;
}


bool ParticleEngine::isDead()
{
	return mFrame > 10;
}