#include "Cannon.h"

#include <string>
#include <iostream>

Cannon::Cannon(glm::vec2 position, float damage, float speed):
	mCannonPosition(position),
	mCanonDamage(damage), 
	mCanonSpeed(speed)
{
 
}


Cannon::~Cannon()
{
}

bool Cannon::LoadCannonTexture(SDL_Renderer* gRenderer)
{

	mCannonTexture.loadSmallTextureFile("Assets/GiantDot.png", gRenderer);

	return true; 
}


void Cannon::updateCannon()
{
	mCannonPosition.x += mCanonSpeed;
}

void Cannon::draw( SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip,  double angle, SDL_Point* center)
{
	//mCannonPosition.x = x;
	//mCannonPosition.y = y;
	//mCannonPosition.x += mCanonSpeed;



	mCannonTexture.renderWithAngle(mCannonPosition.x, mCannonPosition.y, gRenderer, NULL, SDL_FLIP_NONE);
	

}
