#pragma once

#include <glm\glm.hpp>
#include <SDL\SDL.h>
#include <SDL/SDL_image.h>
#include "SDLTexture.h"

class Cannon
{
public:
	
	
	Cannon(glm::vec2 position, float damage, float speed);
	~Cannon();

	bool LoadCannonTexture(SDL_Renderer* gRenderer);
	void draw(SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle = 0.0, SDL_Point* center = NULL);
	void updateCannon();
private:

	float mCanonDamage; 
	float mCanonSpeed = 1.0f;

	glm::vec2 mCannonPosition;

	SDLTexture mCannonTexture; 
	SDL_Texture* mPlayerTexture;

	glm::vec2 m_Dimensions; 
};

