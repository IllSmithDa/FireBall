#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

#include <stdio.h>


class MainGame
{
public:
	MainGame();
	~MainGame();

	bool init();
	

private:

	bool loadMedia();

	void eventHandler();

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//SDL renderer 
	SDL_Renderer* gRenderer = NULL; 

	int SCREEN_WIDTH = 800; 
	int SCREEN_HEIGHT = 600; 
};

