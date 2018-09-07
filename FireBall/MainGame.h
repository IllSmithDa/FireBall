#pragma once



#include "PlayerShip.h"
#include "Cannon.h"
#include <cstdio>
#include <stdio.h>

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <glm\glm.hpp>
#include <IL\il.h>
#include <IL\ilu.h>


#include <string>



#include "SDLTexture.h"
#include "Sprite.h"
#include "InputManager.h"


#include <GL/gl.h>




//keeps track of different animation states 
enum class BossMoveState { LEFT, RIGHT, UP, DOWN, ENTRANCE };

class MainGame
{
public:
	MainGame();
	~MainGame();

	bool init();
	bool initGL();

	BossMoveState m_bossMoveState;

	//Scene sprites
	SDL_Rect gSpriteClips[16];
	SDL_Rect gExplosiongClips[10];
	SDL_Rect MBoss1Clip[10];
	SDL_Rect totalFrame[6];

	//dimensions of sprite 
	static const int SPRITE_WIDTH = 26;
	static const int SPRITE_HEIGHT = 26;

	//maximum velocity of sprite 
	static const int SPRITE_VEL = 10;

	//fps 
	int SCREEN_FPS = 60;

	//sprite position
	int mPosX, mPosY;

	//the velocity of the dot 
	int mVelX, mVelY;

	void render();

	glm::vec2 mPlayerShipPosition;

private:

	bool loadMedia();
	float mSpeed = 20.0f;

	void eventHandler();
	void free();
	void close();

	//sprite class reference 
	Sprite msprite; 

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;


	//create context 
	SDL_GLContext gContext;

	//SDL renderer 
	SDL_Renderer* gRenderer = NULL; 

	//The actual hardware texture
	SDL_Texture* mTexture;

	//reference to sdltexture class
	SDLTexture sdlTexture;
	
	//back ground texture 
	SDLTexture backgroundTexture;
	SDLTexture forefrontTexture; 
	SDLTexture sunTexture;
	Sprite bossTexture;
	SDLTexture spriteTexture;

	PlayerShip mPlayerShip; 
	PlayerShip mCannon;
	PlayerShip mBossShip; 
	PlayerShip mExplosion; 
	
	//World holds all the different rigid bodies and all the different phsyics shapes for 
	//our physics simulation as well as handling simulating 
	std::unique_ptr<b2World> m_world;

	//reference input manager 
	InputManager* mInputManager;

	//position of sprite 
	glm::vec2 mPosition; 

	int SCREEN_WIDTH = 1078; 
	int SCREEN_HEIGHT = 600; 
	int mWidth; 
	int mHeight;

	std::vector<SDL_Rect> mBossCollisionVector;
	std::vector<Cannon> mPlayerCannon;
};

