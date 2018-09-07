#pragma once

#include <SDL\SDL.h>

#include "SDLTexture.h"
#include "InputManager.h"
#include "ParticleEngine.h"
#include <glm\glm.hpp>
#include <Box2D\Box2D.h>


//Particle count
const int TOTAL_PARTICLES = 20;


//keeps track of different animation states 
//enum class PlayerMoveState { STANDING, RUNNING };



class Sprite
{
public:
	Sprite();
	~Sprite();

	//dimensions of sprite 
	static const int SPRITE_WIDTH = 64; 
	static const int SPRITE_HEIGHT = 64;

	//maximum velocity of sprite 
	static const int SPRITE_VEL = 4; 

	//load sprite from file 
	bool loadSpriteFromFile(std::string path, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer);

	//handle events and movement for objects
	void eventHandler(SDL_Event &e);

	//rendering sprite 
	void renderWithAngle(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle =NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	//movement for sprites 
	void move(int SCREEN_WIDTH, int SCREEN_HEIGHT, glm::vec2 shipPosition);

	//render sprite
	void renderSprite(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle = 0,   SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void render(SDL_Renderer* gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int animateframe, SDL_Rect* clip);

	void loadSprite(SDL_Renderer* gRenderer);

	//Angle of rotation
	double degrees = 0;

	int getWidth();
	int getHeight();

	void destroyTexture();

	void update();

	InputManager* m_inputManager;

	glm::vec2 m_position;
	float m_speed = 5.0f;

	void setTexture();

	void free();

	void renderParticles(SDL_Renderer* gRenderer);

	void loadParticles(SDL_Renderer* gRenderer);

	//The particles
	ParticleEngine* particles[TOTAL_PARTICLES];
	SDLTexture gSpriteSheetTexture;

///	PlayerMoveState m_moveState;
	
	void showImage(SDL_Renderer* gRenderer);
	void showShimmerTexture(SDL_Renderer* gRenderer);


	SDLTexture gRedTexture;
	SDLTexture gGreenTexture;
	SDLTexture gBlueTexture;
	SDLTexture gShimmerTexture;
	SDLTexture gSpriteFigure;


	void setAlpha(Uint8 alpha);


	//gets the collision boxes 
	std::vector<SDL_Rect>& getColliders();



	//the body 
	b2Body* m_body;

	//store the friction pointer and create it using the world
	b2Fixture* m_fixture;


	bool checkCollision(SDL_Rect a, SDL_Rect b);

private:

	//World holds all the different rigid bodies and all the different phsyics shapes for 
	//our physics simulation as well as handling simulating 
	std::unique_ptr<b2World> m_world;

	SDLTexture mSpriteTexture; 

	//The actual hardware texture
	SDL_Texture* mTexture;

	//shred acceleration 
	int mVelX, mVelY;

	//particle position
	int mPosParticleX, mPosParticleY;


	//sprite position
	int mPosShipX, mPosShipY;
	 
	glm::vec2 mPlayerShip;

	//number of frames 
	int numFrames;


	int mWidth, mHeight; 

	SDL_RendererFlip mflip = SDL_FLIP_NONE;

	//collision of ships 
	SDL_Rect mShipCollision;

	//collision of ships 
	std::vector<SDL_Rect> mSmallShipCollision;



	//Moves the collision boxes relative to the dot's offset
	//void shiftColliders();
};

