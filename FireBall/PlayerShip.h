#pragma once

#include <glm\glm.hpp>
#include <Box2D\Box2D.h>
#include "DebugRenderer.h"
#include "InputManager.h"
#include "SDLTexture.h"
#include "PlayerCapsule.h"
#include "Cannon.h"
#include "Weapon.h"

class PlayerShip
{

	//keeps track of different animation states 
	enum class PlayerMoveState { STANDING, RUNNING };

public:
	PlayerShip();
	~PlayerShip();

	//maximum velocity of sprite 
	 int SPRITE_VEL = 4;

	PlayerMoveState m_moveState;

	//Angle of rotation
	double degrees = 0;

	void init(std::vector<Cannon> mCannon);
	void initCollisionOnly(int ShipPositionX, int ShipPositionY);
	void bossShipCollisionInit(int ShipPositionX, int ShipPositionY, std::vector<SDL_Rect> & otherCollisionVector);
	void eventHandler(SDL_Event &e, SDL_Renderer* gRenderer, std::vector<Cannon>  *mPlayerCannon);

	void drawShip(); 
	//Gets the collision boxes
	SDL_Rect& getColliders();
	std::vector<SDL_Rect>& getBossColliders();

	void move(SDL_Rect& otherColliders, int ScreenWidth, int ScreenHeight, int BossPositionX, int bossPositionY, glm::vec2 BossPosition, b2World *world, std::vector<SDL_Rect> & otherCollisionVector);
	bool checkCollision(SDL_Rect& a, SDL_Rect& b);

	bool checkVectorCollision(std::vector<SDL_Rect>& objectA, std::vector<SDL_Rect>& objectB);

	bool loadPlayerShipFromFile(std::string path, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer);
	bool loadBossShip(std::string path, SDL_Renderer* gRenderer);

	void renderPlayerShip(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center);
	void renderBossShip(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center, b2World* world);
	void render(SDL_Renderer* gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int animateframe, SDL_Rect* clip, SDL_Rect* ExplosionClip);
	void loadSprite(SDL_Renderer* gRenderer);

	SDLTexture gSpriteFigure;
	SDLTexture gExplosionTexture;

	void ExplosionAnimation();
	
	int getEnergyShield() { return playerEnergyShield; }

	SDL_Texture* getPlayerTexture() { return mPlayerTexture; }

	glm::vec2 getPlayerShipPosition() { return mPlayerShipPosition; }

	std::vector<SDL_Rect> & getPlayerCollisionVector() { return mPlayerCollisionVector; }
	//std::vector<SDL_Rect> & getBossCollisionVector() { return mBossCollisionVector; }
	void freePlayerTexture();
	bool getCannonStatus() { return isCannonOn; }

	bool loadCannon(std::string path, SDL_Renderer* gRenderer);
	void drawCannon(glm::vec2 cannonPosition, SDL_Rect* clip, SDL_Renderer* gRenderer);

	int isCannonOn = false;

	void AddWeapon(Weapon* weapon);
	
private:

	void ShiftVectorPlayerColliders();
	void ShiftVectorOtherColliders(glm::vec2 bossShipPosition, std::vector<SDL_Rect> & otherCollisionVector);

	int playerEnergyShield = 100; 

	SDL_RendererFlip mflip = SDL_FLIP_HORIZONTAL;

	//player ship position 
	glm::vec2 mPlayerShipPosition;

	//boss ship position
	glm::vec2 mBossShipPosition;

	//The X and Y offsets of the player ship
	int mPosX = 200, mPosY = 200;

	//The actual hardware texture
	SDL_Texture* mPlayerTexture;
	SDL_Texture* mBossTexture; 
	SDL_Texture* mCannonTexture;

	//The X and y offsets of the boss ship 
	int mBossX, mBossY; 

	// THe velocity of boss ship
	int mBossVelX, mBossVelY; 

	//The velocity of the ship
	int mVelX = 0;
	int mVelY = 0;

	//Ship's collision boxes
	SDL_Rect mColliders;


	//Boss ship collision boxes 
	std::vector<SDL_Rect> mBossColliders;

	int m_Speed; 
	glm::vec2 m_Dimensions; 
	glm::vec2 m_BossDimensions; 
	glm::vec2 m_CannonDimensions; 


	glm::vec2 m_ScreenDimensions;

	glm::vec2 m_Position; 

	InputManager* m_InputManager; 
	SDLTexture m_SDLTexture; 
	PlayerCapsule m_PlayerCapsule; 
	DebugRenderer m_DebugRenderer;

	SDLTexture mSpriteTexture;

	//change animatin over time and initiate it to 0
	float m_animTime = 0.9f;

	//Moves the collision boxes relative to the shi['s offset
	//void myShiftColliders();

	//moves collision boxes relative to the bossship's offset 
	//void bossShiftCollider(int BossPositionX, int bossPositionY);

	//body of vectors for boss ship 
	//std::vector<SDL_Rect> mBossCollisionVector; 

	std::vector<SDL_Rect> mPlayerCollisionVector;

	//Cannon class 
	std::vector<Cannon> * mPlayerCannon; 

	std::vector<Weapon*> mPlayerWeapon;
		
	int mCurrentWeaponIndex;

};

