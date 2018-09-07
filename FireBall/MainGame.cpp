#include "MainGame.h"
#include <iostream>
//Scene textures
SDLTexture gDotTexture;



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
		system("Pause");
		success = false; 
		
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create Double Buffered Window
	//	glutInitDisplayMode(GLUT_DOUBLE);

	//	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
      //	glutCreateWindow("OpenGL");
	
		//Create window
		gWindow = SDL_CreateWindow("Fireball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
		if(gWindow == NULL)
		{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			system("Pause");
			success = false; 
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			
			if (gContext == NULL)
			{

				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				system("Pause");
			
				success = false;


			}
			//Do post window/context creation initialization


			else 
			{
				
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					system("Pause");
					
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					system("Pause");
				
					success = false;
				}
				
			}

			//Initialize DevIL
			ilInit();
			ilClearColour(255, 255, 255, 000);

			//Check for error
			ILenum ilError = ilGetError();
			if (ilError != IL_NO_ERROR)
			{
				printf("Error initializing DevIL! %s\n", iluErrorString(ilError));

				system("Pause");
				return false;
			}

			
			//create renderer for window 
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				system("Pause");
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
					system("Pause");
					success = false;
				}	
			}
		}
	}

	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		system("Pause");
		success = false; 
	}
	eventHandler();
	return success; 
}

bool MainGame::loadMedia()
{
	//mCannon.init(mPlayerCannon);
	

	//initialization flag 
	bool success = true;

	//load texture
	 backgroundTexture.loadfromFile("Assets/space1.png", SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

	// msprite.loadSpriteFromFile("Assets/foo2.png", 50, 50, gRenderer);

	// msprite.loadSpriteFromFile("Assets/blue_ninja.png", 23, 23, gRenderer);

	// msprite.loadSpriteFromFile("Assets/ship3.png", 23, 23, gRenderer);
	// msprite.loadSpriteFromFile("Assets/ship3.png", 23, 23, gRenderer);

	 mPlayerShip.loadPlayerShipFromFile("Assets/ship3.png", SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

	 sunTexture.loadSmallTextureFile("Assets/planet2.png", gRenderer);

	 //bossTexture.loadSpriteFromFile("Assets/bigship1.png", 100 ,100 , gRenderer);
	 mBossShip.loadBossShip("Assets/ship4.png", gRenderer);


	 for (unsigned int i = 0; i < mPlayerCannon.size(); i++) {
		 mPlayerCannon[i].LoadCannonTexture(gRenderer);
	 }
	 
	 //mCannon.loadCannon("Assets/GiantDot.png", gRenderer);
	// mExplosion.loadBossShip("Assets/Explosion.png", gRenderer);
	 
	//spriteTexture.loadSmallTextureFile("Assets/foo2.png", gRenderer);

	//GLBackGround.loadTextureFromFile("Assets/grass1.png");
	//GLForeGround.loadTextureFromFile("Assets/block1.png");
	 
	 
	 
	//Set sprite clips

	 /*
	 gSpriteClips[0].x = 0;
	 gSpriteClips[0].y = 0;
	 gSpriteClips[0].w = 64;
	 gSpriteClips[0].h = 205;

	 gSpriteClips[1].x = 64;
	 gSpriteClips[1].y = 0;
	 gSpriteClips[1].w = 64;
	 gSpriteClips[1].h = 205;

	 gSpriteClips[2].x = 128;
	 gSpriteClips[2].y = 0;
	 gSpriteClips[2].w = 64;
	 gSpriteClips[2].h = 205;

	 gSpriteClips[3].x = 196;
	 gSpriteClips[3].y = 0;
	 gSpriteClips[3].w = 64;
	 gSpriteClips[3].h = 205;
	 
	 */

	 /*
	 gSpriteClips[0].x = 0;
	 gSpriteClips[0].y = 64;
	 gSpriteClips[0].w = 64;
	 gSpriteClips[0].h = 64;

	 */

	
	 gSpriteClips[0].x = 0;
	 gSpriteClips[0].y = 0;
	 gSpriteClips[0].w = 64;
	 gSpriteClips[0].h = 64;

	 gSpriteClips[1].x = 64;
	 gSpriteClips[1].y = 0;
	 gSpriteClips[1].w = 64;
	 gSpriteClips[1].h = 64;

	 gSpriteClips[2].x = 128;
	 gSpriteClips[2].y = 0;
	 gSpriteClips[2].w = 64;
	 gSpriteClips[2].h = 64;

	 gSpriteClips[3].x = 192;
	 gSpriteClips[3].y = 0;
	 gSpriteClips[3].w = 64;
	 gSpriteClips[3].h = 64;

	 gSpriteClips[4].x = 256;
	 gSpriteClips[4].y = 0;
	 gSpriteClips[4].w = 64;
	 gSpriteClips[4].h = 64;

	 gSpriteClips[5].x = 320;
	 gSpriteClips[5].y = 0;
	 gSpriteClips[5].w = 64;
	 gSpriteClips[5].h = 64;



	 gExplosiongClips[0].x = 0; 
	 gExplosiongClips[0].y = 0; 
	 gExplosiongClips[0].w = 64;
	 gExplosiongClips[0].h = 64;
	 
	 gExplosiongClips[1].x = 64;
	 gExplosiongClips[1].y = 0;
	 gExplosiongClips[1].w = 64;
	 gExplosiongClips[1].h = 64;

	 gExplosiongClips[2].x = 128;
	 gExplosiongClips[2].y = 0;
	 gExplosiongClips[2].w = 64;
	 gExplosiongClips[2].h = 64;

	 gExplosiongClips[3].x = 64*3;
	 gExplosiongClips[3].y = 0;
	 gExplosiongClips[3].w = 64;
	 gExplosiongClips[3].h = 64;

	 gExplosiongClips[4].x = 64*4;
	 gExplosiongClips[4].y = 0;
	 gExplosiongClips[4].w = 64;
	 gExplosiongClips[4].h = 64;

	 gExplosiongClips[5].x = 64 * 5;
	 gExplosiongClips[5].y = 0;
	 gExplosiongClips[5].w = 64;
	 gExplosiongClips[5].h = 64;

	 gExplosiongClips[6].x = 64 * 6;
	 gExplosiongClips[6].y = 0;
	 gExplosiongClips[6].w = 64;
	 gExplosiongClips[6].h = 64;

	 gExplosiongClips[7].x = 64 * 7;
	 gExplosiongClips[7].y = 0;
	 gExplosiongClips[7].w = 64;
	 gExplosiongClips[7].h = 64;

	 gExplosiongClips[8].x = 64 * 8;
	 gExplosiongClips[8].y = 0;
	 gExplosiongClips[8].w = 64;
	 gExplosiongClips[8].h = 64;

	 gExplosiongClips[9].x = 64 * 9;
	 gExplosiongClips[9].y = 0;
	 gExplosiongClips[9].w = 64;
	 gExplosiongClips[9].h = 64;

	 gExplosiongClips[10].x = 64 * 10;
	 gExplosiongClips[10].y = 0;
	 gExplosiongClips[10].w = 64;
	 gExplosiongClips[10].h = 64;


	 MBoss1Clip[0].x = 0; 
	 MBoss1Clip[0].y = 0;
	 MBoss1Clip[0].w = 512; 
	 MBoss1Clip[0].h = 512; 

	 MBoss1Clip[1].x = 512;
	 MBoss1Clip[1].y = 0;
	 MBoss1Clip[1].w = 512;
	 MBoss1Clip[1].h = 512;

	 MBoss1Clip[2].x = 512 *2;
	 MBoss1Clip[2].y = 0;
	 MBoss1Clip[2].w = 512;
	 MBoss1Clip[2].h = 512;

	 MBoss1Clip[3].x = 512 * 3;
	 MBoss1Clip[3].y = 0;
	 MBoss1Clip[3].w = 512;
	 MBoss1Clip[3].h = 512;

	 MBoss1Clip[4].x = 512*4;
	 MBoss1Clip[4].y = 0;
	 MBoss1Clip[4].w = 512;
	 MBoss1Clip[4].h = 512;

	 MBoss1Clip[5].x = 512*5;
	 MBoss1Clip[5].y = 0;
	 MBoss1Clip[5].w = 512;
	 MBoss1Clip[5].h = 512;

	 MBoss1Clip[6].x = 512*6;
	 MBoss1Clip[6].y = 0;
	 MBoss1Clip[6].w = 512;
	 MBoss1Clip[6].h = 512;


	 mBossCollisionVector.resize(35);
	 //Initialize the collision boxes' width and height
	 mBossCollisionVector[0].w = 321;
	 mBossCollisionVector[0].h = 2;

	 mBossCollisionVector[1].w = 316;
	 mBossCollisionVector[1].h = 2;

	 mBossCollisionVector[2].w = 301;
	 mBossCollisionVector[2].h = 2;

	 mBossCollisionVector[3].w = 287;
	 mBossCollisionVector[3].h = 2;

	 mBossCollisionVector[4].w = 275;
	 mBossCollisionVector[4].h = 2;

	 mBossCollisionVector[5].w = 263;
	 mBossCollisionVector[5].h = 2;

	 mBossCollisionVector[6].w = 252;
	 mBossCollisionVector[6].h = 2;

	 mBossCollisionVector[7].w = 243;
	 mBossCollisionVector[7].h = 2;

	 mBossCollisionVector[8].w = 234;
	 mBossCollisionVector[8].h = 2;

	 mBossCollisionVector[9].w = 229;
	 mBossCollisionVector[9].h = 2;

	 mBossCollisionVector[10].w = 224;
	 mBossCollisionVector[10].h = 2;

	 mBossCollisionVector[11].w = 220;
	 mBossCollisionVector[11].h = 2;

	 mBossCollisionVector[12].w = 217;
	 mBossCollisionVector[12].h = 2;

	 mBossCollisionVector[13].w = 214;
	 mBossCollisionVector[13].h = 4;

	 mBossCollisionVector[14].w = 211;
	 mBossCollisionVector[14].h = 4;

	 mBossCollisionVector[15].w = 208;
	 mBossCollisionVector[15].h = 4;

	 mBossCollisionVector[16].w = 207;
	 mBossCollisionVector[16].h = 46;

	 mBossCollisionVector[17].w = 300;
	 mBossCollisionVector[17].h = 299;

	 mBossCollisionVector[18].w = 207;
	 mBossCollisionVector[18].h = 46;

	 mBossCollisionVector[19].w = 208;
	 mBossCollisionVector[19].h = 4;

	 mBossCollisionVector[20].w = 211;
	 mBossCollisionVector[20].h = 4;

	 mBossCollisionVector[21].w = 214;
	 mBossCollisionVector[21].h = 4;

	 mBossCollisionVector[22].w = 217;
	 mBossCollisionVector[22].h = 2;

	 mBossCollisionVector[23].w = 220;
	 mBossCollisionVector[23].h = 2;

	 mBossCollisionVector[24].w = 224;
	 mBossCollisionVector[24].h = 2;

	 mBossCollisionVector[25].w = 229;
	 mBossCollisionVector[25].h = 2;

	 mBossCollisionVector[26].w = 234;
	 mBossCollisionVector[26].h = 2;

	 mBossCollisionVector[27].w = 243;
	 mBossCollisionVector[27].h = 2;

	 mBossCollisionVector[28].w = 252;
	 mBossCollisionVector[28].h = 2;

	 mBossCollisionVector[29].w = 263;
	 mBossCollisionVector[29].h = 2;

	 mBossCollisionVector[30].w = 275;
	 mBossCollisionVector[30].h = 2;

	 mBossCollisionVector[31].w = 287;
	 mBossCollisionVector[31].h = 2;

	 mBossCollisionVector[32].w = 301;
	 mBossCollisionVector[32].h = 2;

	 mBossCollisionVector[33].w = 316;
	 mBossCollisionVector[33].h = 2;

	 mBossCollisionVector[34].w = 321;
	 mBossCollisionVector[34].h = 2;

	

	 mPlayerShip.loadSprite(gRenderer);
	// msprite.loadParticles(gRenderer);


	 mPlayerShip.AddWeapon(new Weapon("Plasma Cannon"));

	return success;
}

void MainGame::eventHandler()
{
	//main loop flag
	bool quit = false;

	//mInputManager->update();

	//The background scrolling offset
	int scrollingOffset = 0;
	int bossScrollingx = SCREEN_WIDTH;
	int bossScrollingy = SCREEN_HEIGHT / 16;
	 

	glm::vec2 bossPosition; 
	bossPosition.x = SCREEN_WIDTH;
	bossPosition.y = SCREEN_HEIGHT / 16;

	int upwardVelcityY = 1;
	int bossVelocityx = 1; 
	int bossVeloctiyy = 1; 
	//int bossAcceleration = 4; 
	int sunscrolling = -sunTexture.getWidth();
	glm::vec2 cannonPosition = mCannon.getPlayerShipPosition();


	int bossxmovement = 0; 
	int frameUntilMovement = 0;

	int frame = 0;
	int ExplosionFrame = 0;
	int BossFrame = 0; 

	//while application is running
	while (!quit)
	{

		SDL_Event evnt;
		//Will keep looping until there are no more events to process
		while (SDL_PollEvent(&evnt) != 0)
		{
			//User requests quit
			if (evnt.type == SDL_QUIT)
			{
				quit = true;
			}
		


			//Define the gravity that the world will use using the Box2D's vector class
			b2Vec2 gravity(0.0f, 0.0f);


			//set up the world and pass in the gravity 
			m_world = std::make_unique<b2World>(gravity);


			mPlayerShip.eventHandler(evnt, gRenderer, &mPlayerCannon);
			

			for (unsigned int i = 0; i < mPlayerCannon.size(); i++) {
				mPlayerCannon[i].updateCannon();
			}
		}
		//end of inner while loop
		
		
		if (m_bossMoveState == BossMoveState::ENTRANCE)
		{
			bossPosition.x -= bossVelocityx;

		}
		
		if (m_bossMoveState == BossMoveState::DOWN) 
		{
			bossVeloctiyy = -1;
			bossPosition.y -= bossVeloctiyy;
		}
		if (m_bossMoveState == BossMoveState::UP) 
		{
			//bossVeloctiyy = 1;
			bossPosition.y -= bossVeloctiyy;
		}
		if (m_bossMoveState == BossMoveState::LEFT)
		{
			bossPosition.x -= bossVelocityx;
		}
		if (m_bossMoveState == BossMoveState::RIGHT)
		{
			//bossScrollingx = bossScrollingx;

			bossVelocityx = -1;
			bossPosition.x -= bossVelocityx;
		}


		m_bossMoveState = BossMoveState::ENTRANCE;


		 if (bossPosition.x < SCREEN_WIDTH / 2)
		{
			bossVelocityx = 0;

		}
	
		 //Set the collision
		 SDL_Rect BossShipCollision;
		 BossShipCollision.x = bossPosition.x +100;
		 BossShipCollision.y = bossPosition.y +100;
		 BossShipCollision.w = 300;
		 BossShipCollision.h = 300;


		 mPlayerShipPosition.x = 50;
		 mPlayerShipPosition.y = 50;

		 mPlayerShip.initCollisionOnly(mPlayerShipPosition.x, mPlayerShipPosition.y);

		 mBossShip.bossShipCollisionInit(bossPosition.x, bossPosition.y, mBossCollisionVector);

			
		 mPlayerShip.move(BossShipCollision, SCREEN_WIDTH, SCREEN_HEIGHT, bossScrollingx, bossScrollingy, bossPosition, m_world.get(), mBossCollisionVector);

		//Scroll background
		--scrollingOffset;
		if (scrollingOffset < -backgroundTexture.getWidth())
		{
			scrollingOffset = 0;
		}

		++++sunscrolling;
		

		


		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

	
		SDL_Rect* Boss1Clip = &MBoss1Clip[BossFrame / 7];


	//Render background
		backgroundTexture.renderWithAngle(scrollingOffset, 0, gRenderer, NULL, SDL_FLIP_NONE);
		backgroundTexture.renderWithAngle(scrollingOffset + backgroundTexture.getWidth(), 0, gRenderer, NULL, SDL_FLIP_NONE);
		mBossShip.renderBossShip( bossPosition.x, bossPosition.y, gRenderer, Boss1Clip, SDL_FLIP_NONE, NULL, NULL, m_world.get());
		sunTexture.renderWithAngle(sunscrolling, 0, gRenderer, NULL, SDL_FLIP_NONE);

		//Render current frame
		SDL_Rect* currentClip = &gSpriteClips[frame / 10];
		SDL_Rect* explosionClip = &gExplosiongClips[ExplosionFrame / 3];
		


		mPlayerShip.render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, frame , currentClip, explosionClip);

		

		//Render current frame
		//SDL_Rect* currentClip = &gSpriteClips[frame / 10];
		//msprite.renderWithAngle((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip, gRenderer);

		//Render quad
		//render();

	
		//draw the bullets 
		for (unsigned int i = 0; i < mPlayerCannon.size(); i++) {
			mPlayerCannon[i].draw(gRenderer, NULL, SDL_FLIP_NONE);
		}
	
	//	SDL_GL_SwapWindow(gWindow);
		SDL_RenderPresent(gRenderer);

	
		

		if (mPlayerShip.getEnergyShield() == 0) 
		{
		
			++ExplosionFrame;


			if (ExplosionFrame / 3 >= 10) {

				ExplosionFrame = 1000;

				mPlayerShip.freePlayerTexture(); 
			}


		}
		//Go to next frame
		++frame;
		//Update screen

		if (frame / 10 >= 6)
		{
			frame = 0;
		}

		//Go to next fram
		++BossFrame; 
		if (BossFrame / 7 >= 7)
		{
			BossFrame = 0; 
		}



	//Update screen
	//	SDL_GL_SwapWindow(gWindow);
	}
}



void MainGame::free()
{



	//free texture if it exists 
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0; 
		mHeight = 0;
	}

	sdlTexture.free();

}

void MainGame::close()
{
	backgroundTexture.free();
	forefrontTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



void MainGame::render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Render quad
	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	
}

bool MainGame::initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	/* Depth buffer setup */
	glClearDepth(1.0f);

	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);

	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);
	

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		system("Pause");
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		system("Pause"); 
		success = false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	return success;
}
