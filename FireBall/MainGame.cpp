#include "MainGame.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

bool MainGame::init() 
{

	//initialization flag 
	bool success = true; 

	//init SDL 
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false; 
	}
	else
	{
		//set texture filter to linear 
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled");

		}
	
		//Create window
		gWindow = SDL_CreateWindow("Fireball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if(gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false; 
		}
		else
		{
			//create renderer for window 
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false; 
			}
			else
			{
				//initialize renderer color 
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0, 0xff);

				//Initialize PNG loading 
				int imgFlags = IMG_INIT_PNG; 
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError());
					success = false; 
				}

			}
		}
	}

	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		success = false; 
	}

	eventHandler();

	return success; 
}

bool MainGame::loadMedia()
{
	//initialization flag 
	bool success = true;

	

	return success;
}

void MainGame::eventHandler()
{
	//main loop flag
	bool quit = false; 

	//event handler 
	SDL_Event e; 

	//while application is running
	while (!quit)
	{	
		//handle events on que
		while (SDL_PollEvent(&e) != 0)
		{
			//user quits 
			if (e.type == SDL_QUIT)
			{
				quit = true; 
			}
		}

	}




}