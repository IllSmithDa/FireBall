#include "PlayerShip.h"
#include <string>
#include <iostream>

//keeps track of different animation states 
enum class PlayerMoveState { STANDING, MOVING};
//Walking animation
const int WALKING_ANIMATION_FRAMES = 1;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

PlayerShip::PlayerShip()
{
}


PlayerShip::~PlayerShip()
{
}


void PlayerShip::init(std::vector<Cannon> mCannon)
{


}



void PlayerShip::initCollisionOnly(int ShipPositionX, int ShipPositionY)
{

}


void PlayerShip::bossShipCollisionInit(int ShipPositionX, int ShipPositionY, std::vector<SDL_Rect> & otherCollisionVector)
{

	//Initialize the offsets
	mBossShipPosition.x = ShipPositionX; // 1100 / 2;
	mBossShipPosition.y = ShipPositionY; // 600 / 9;


	//Initialize colliders relative to position
	ShiftVectorOtherColliders(mBossShipPosition, otherCollisionVector);
}



SDL_Rect& PlayerShip::getColliders()
{

	return mColliders;
}

std::vector<SDL_Rect>& PlayerShip::getBossColliders()
{
	return mBossColliders;
}


void PlayerShip::move(SDL_Rect& otherColliders, int ScreenWidth, int ScreenHeight, int BossPositionX, int bossPositionY, glm::vec2 BossPosition, b2World *world, std::vector<SDL_Rect> & otherCollisionVector)
{
	//Move the dot left or right
	mPlayerShipPosition.x += mVelX;

	ShiftVectorPlayerColliders();
	ShiftVectorOtherColliders(BossPosition, otherCollisionVector);


	//If the dot collided or went too far to the left or right
	if ((mPlayerShipPosition.x < 0) || (mPlayerShipPosition.x > ScreenWidth - (m_Dimensions.x)) || checkVectorCollision(mPlayerCollisionVector, otherCollisionVector) /*|| checkCollision(mColliders, otherColliders)*/)
	{
		//Move back
		mPlayerShipPosition.x -= mVelX;

		ShiftVectorPlayerColliders();
		ShiftVectorOtherColliders(BossPosition, otherCollisionVector);
		//mColliders.x = mPlayerShipPosition.x;
		//myShiftColliders();
		//bossShiftCollider(BossPositionX, bossPositionY);
	}

	//Move the dot up or down
	mPlayerShipPosition.y += mVelY;
	ShiftVectorPlayerColliders();
	ShiftVectorOtherColliders(BossPosition, otherCollisionVector);


	if ((mPlayerShipPosition.y < 0) || (mPlayerShipPosition.y > ScreenHeight - (m_Dimensions.y )) || checkVectorCollision(mPlayerCollisionVector, otherCollisionVector) /*|| checkCollision(mColliders, otherColliders)*/)
	{
		//Move back
		mPlayerShipPosition.y -= mVelY;

		ShiftVectorPlayerColliders();
		ShiftVectorOtherColliders(BossPosition, otherCollisionVector);
	}

	std::cout << " m_Dimesions.x = " << m_Dimensions.x << std::endl;
	std::cout << "m_Dimeions.y = " << m_Dimensions.y << std::endl;
	std::cout << "mColliders.h =" << mColliders.h << std::endl;
	std::cout << "mColliders.w = " << mColliders.w << std::endl;


}	

bool PlayerShip::checkCollision(SDL_Rect& a, SDL_Rect& b)
{

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{

		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	else {


		playerEnergyShield = 0; 
		//If none of the sides from A are outside B

		SPRITE_VEL = 0;
		mVelX = 0; 
		mVelY = 0; 
		return true;

	}
}

bool PlayerShip::loadPlayerShipFromFile(std::string path, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer)
{

	//initialization flag
	bool success = true;

	SDL_Texture* newTexture = NULL;

	//load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s\n", SDL_GetError(), IMG_GetError());
	}
	else
	{
		//color key image 
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGBA(loadedSurface->format, 0, 0xFF, 0xFF, 0xFF));

		//create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s!, SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//get image dimensions 
			m_Dimensions.x = 64;
			m_Dimensions.y = 64;
		}

		//get rid of old loaded surface 
		SDL_FreeSurface(loadedSurface);
	}

	mPlayerTexture = newTexture;


	//Create the necessary SDL_Rects
	mBossColliders.resize(1);

	//Initialize the velocity
	mBossVelX = 0;
	mBossVelY = 0;

	//Initialize the collision boxes' width and height
	mBossColliders[0].w = 350;
	mBossColliders[0].h = 450;

	return mPlayerTexture != NULL;

}


bool PlayerShip::loadBossShip(std::string path, SDL_Renderer* gRenderer)
{

	//initialization flag
	bool success = true;

	SDL_Texture* newTexture = NULL;

	//load image at specified path 
	SDL_Surface* loadedBossSurface = IMG_Load(path.c_str());
	if (loadedBossSurface == NULL)
	{
		printf("Unable to load image %s\n", SDL_GetError(), IMG_GetError());
	}
	else
	{
		//color key image 
		SDL_SetColorKey(loadedBossSurface, SDL_TRUE, SDL_MapRGBA(loadedBossSurface->format, 0, 0xFF, 0xFF, 0xFF));

		//create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedBossSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s!, SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//get image dimensions 
			m_BossDimensions.x = loadedBossSurface->w;
			m_BossDimensions.y = loadedBossSurface->h;
		}

		//get rid of old loaded surface 
		SDL_FreeSurface(loadedBossSurface);
	}

	mBossTexture = newTexture;

	return mBossTexture != NULL;

}

void PlayerShip::renderPlayerShip(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Dimensions.x, m_Dimensions.y };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mPlayerTexture, clip, &renderQuad, angle, center, flip);


	//Update screen
	//SDL_RenderPresent(gRenderer);

}

void PlayerShip::renderBossShip(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center, b2World* world)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_BossDimensions.x, m_BossDimensions.y };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mBossTexture, clip, &renderQuad, angle, center, flip);


	//Update screen
	//SDL_RenderPresent(gRenderer);


}

void PlayerShip::eventHandler(SDL_Event &e, SDL_Renderer* gRenderer, std::vector<Cannon>  *mPlayerCannon)
{

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			mVelY -= SPRITE_VEL;

			

			if (mVelX == 0)
			{
				m_moveState = PlayerMoveState::STANDING;
			}
			break;
		case SDLK_s:
			mVelY += SPRITE_VEL;

			if (mVelX == 0)
			{
				m_moveState = PlayerMoveState::STANDING;

			}
			break;
		case SDLK_a:
			mVelX -= SPRITE_VEL;
			m_moveState = PlayerMoveState::RUNNING;


			
			if (mflip == SDL_FLIP_NONE)
			{
			//	mflip = SDL_FLIP_NONE;
			}
			else if (mflip == SDL_FLIP_HORIZONTAL)
			{
			//	mflip = SDL_FLIP_NONE;
			}
			

			break;
		case SDLK_d:
			mVelX += SPRITE_VEL;
			m_moveState = PlayerMoveState::RUNNING;
			isCannonOn = true;
			
			if (mflip == SDL_FLIP_NONE)
			{
				//mflip = SDL_FLIP_HORIZONTAL;
			}
			else if (mflip == SDL_FLIP_HORIZONTAL)
			{
				//mflip = SDL_FLIP_HORIZONTAL;
			}

			

			break;
		case SDLK_SPACE:


			if (mCurrentWeaponIndex != -1) {

				int mCannonSpeed = 1.0f;

				mPlayerWeapon[mCurrentWeaponIndex]->update(/*m_InputManager->isKeyDown(SDLK_SPACE),*/
					mPlayerShipPosition, mCannonSpeed, *mPlayerCannon);


			}

		//	mPlayerCannon.push_back(new Cannon(mPlayerShipPosition, 10.0f, 1.0f));

			//draw the bullets 
		//	for (unsigned int i = 0; i < mPlayerCannon.size(); i++) {

			//	mPlayerCannon[i]->draw(mPlayerShipPosition.x, mPlayerShipPosition.y, gRenderer, NULL, SDL_FLIP_NONE);
		//	}
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			mVelY += SPRITE_VEL;

			break;
		case SDLK_s:
			mVelY -= SPRITE_VEL;

			break;
		case SDLK_a:

			mVelX += SPRITE_VEL;
			if (mVelX == 0) {
				m_moveState = PlayerMoveState::STANDING;
			}
			break;
		case SDLK_d:
			mVelX -= SPRITE_VEL;

			if (mVelX == 0)
			{

				m_moveState = PlayerMoveState::STANDING;
			}
			break;

		case SDLK_SPACE:
			break; 

		}
	}

	else if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			degrees -= 2.5;
			break;

		case SDLK_e:
			degrees += 2.5;
			break;
		}
	}


	if (mCurrentWeaponIndex != -1) {

		int mCannonSpeed = 1.0f;

		mPlayerWeapon[mCurrentWeaponIndex]->update(/*m_InputManager->isKeyDown(SDLK_SPACE),*/
			mPlayerShipPosition, mCannonSpeed, *mPlayerCannon);


	}

}


void PlayerShip::loadSprite(SDL_Renderer* gRenderer)
{
	//Initialize the collision boxes' width and height
	mColliders.w = 64;
	mColliders.h = 64;

	new Cannon(mPlayerShipPosition, 10.0f, 10.0f);

	gSpriteFigure.loadSmallTextureFile("Assets/ship3.png", gRenderer);
	gSpriteFigure.loadSmallTextureFile("Assets/ship3.png", gRenderer);
	gExplosionTexture.loadSmallTextureFile("Assets/Explosion.png", gRenderer);
	

	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 64;
	gSpriteClips[0].w = 64;
	gSpriteClips[0].h = 64;

	
	//Create the necessary SDL_Rects
//	mBossCollisionVector.resize(5);
	mPlayerCollisionVector.resize(5);


	//intialize player ship
	mPlayerCollisionVector[0].h = 22;
	mPlayerCollisionVector[0].w = 56;

	mPlayerCollisionVector[1].h = 6;
	mPlayerCollisionVector[1].w = 26;

	mPlayerCollisionVector[2].h = 4;
	mPlayerCollisionVector[2].w = 18;

	mPlayerCollisionVector[3].h = 7;
	mPlayerCollisionVector[3].w = 26;

	mPlayerCollisionVector[4].h = 4;
	mPlayerCollisionVector[4].w = 18;

	
	
	//Initialize colliders relative to position
		ShiftVectorPlayerColliders();
		//ShiftVectorBossColliders();

}
void PlayerShip::render(SDL_Renderer* gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int animateframe, SDL_Rect* clip, SDL_Rect* ExplosionClip)
{
	int snowball = 100;
	//Show particles on top of dot
	//renderParticles(gRenderer);

	//numFrames = animateframe;

	if (m_moveState == PlayerMoveState::RUNNING)
	{


		//int frame = 0;
		//Render current frame
		//SDL_Rect* currentClip = &gSpriteClips[animateframe / 10];

		//renderSprite(mPosShipX, mPosShipY, gRenderer, currentClip);

		if (playerEnergyShield == 0)
		{

			//int frame = 0;
			//Render current frame
			//SDL_Rect* currentClip = &gSpriteClips[animateframe / 10];


			//renderSprite(mPosShipX, mPosShipY, gRenderer, currentClip);
			gExplosionTexture.renderWithAngle(mPlayerShipPosition.x, mPlayerShipPosition.y, gRenderer, ExplosionClip, mflip);

			//playerEnergyShield = 100;

			snowball = 200; 

		}
		else {
			gSpriteFigure.renderWithAngle(mPlayerShipPosition.x, mPlayerShipPosition.y, gRenderer, clip, mflip);
		}
	}
	else if (m_moveState == PlayerMoveState::STANDING)
	{
		if (playerEnergyShield == 0)
		{
			//renderSprite(mPosShipX, mPosShipY, gRenderer, currentClip);
			gExplosionTexture.renderWithAngle(mPlayerShipPosition.x, mPlayerShipPosition.y, gRenderer, ExplosionClip, mflip);	
		}
		else{
		gSpriteFigure.renderWithAngle(mPlayerShipPosition.x, mPlayerShipPosition.y, gRenderer, clip, mflip);
		}
	}

	if (snowball == 200)
	{
		gExplosionTexture.renderWithAngle(mPlayerShipPosition.x, mPlayerShipPosition.y, gRenderer, ExplosionClip, mflip);

	}

}

void PlayerShip::ExplosionAnimation()
{
	int frame = 70;
	frame++;
}

bool PlayerShip::checkVectorCollision(std::vector<SDL_Rect>& objectA, std::vector<SDL_Rect>& objectB)
{

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Go through the A boxes
	for (int Abox = 0; Abox < objectA.size(); Abox++)
	{
		//Calculate the sides of rect A
		leftA = objectA[Abox].x;
		rightA = objectA[Abox].x + objectA[Abox].w;
		topA = objectA[Abox].y;
		bottomA = objectA[Abox].y + objectA[Abox].h;

		//Go through the B boxes
		for (int Bbox = 0; Bbox < objectB.size(); Bbox++)
		{
			//Calculate the sides of rect B
			leftB = objectB[Bbox].x;
			rightB = objectB[Bbox].x + objectB[Bbox].w;
			topB = objectB[Bbox].y;
			bottomB = objectB[Bbox].y + objectB[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				playerEnergyShield = 0; 
				//A collision is detected
				return true;
			}
		}
	}

	//If neither set of collision boxes touched
	return false;
}

void PlayerShip::ShiftVectorPlayerColliders()
{
	mPlayerCollisionVector[0].x = mPlayerShipPosition.x + 0;
	mPlayerCollisionVector[0].y = mPlayerShipPosition.y + 21;

	mPlayerCollisionVector[1].x = mPlayerShipPosition.x + 18;
	mPlayerCollisionVector[1].y = mPlayerShipPosition.y + 11;

	mPlayerCollisionVector[2].x = mPlayerShipPosition.x + 30;
	mPlayerCollisionVector[2].y = mPlayerShipPosition.y + 4;

	mPlayerCollisionVector[3].x = mPlayerShipPosition.x + 18;
	mPlayerCollisionVector[3].y = mPlayerShipPosition.y + 43;

	mPlayerCollisionVector[4].x = mPlayerShipPosition.x + 30;
	mPlayerCollisionVector[4].y = mPlayerShipPosition.y + 50;
}


void PlayerShip::ShiftVectorOtherColliders(glm::vec2 bossShipPosition, std::vector<SDL_Rect> & otherCollisionVector)
{
	otherCollisionVector[0].x = bossShipPosition.x +93;
	otherCollisionVector[0].y = bossShipPosition.y +16;

	otherCollisionVector[1].x = bossShipPosition.x + 98;
	otherCollisionVector[1].y = bossShipPosition.y + 18;

	otherCollisionVector[2].x = bossShipPosition.x + 108;
	otherCollisionVector[2].y = bossShipPosition.y + 20;

	otherCollisionVector[3].x = bossShipPosition.x + 118;
	otherCollisionVector[3].y = bossShipPosition.y + 22;

	otherCollisionVector[4].x = bossShipPosition.x + 126;
	otherCollisionVector[4].y = bossShipPosition.y + 24;

	otherCollisionVector[5].x = bossShipPosition.x + 134;
	otherCollisionVector[5].y = bossShipPosition.y + 26;

	otherCollisionVector[6].x = bossShipPosition.x + 141;
	otherCollisionVector[6].y = bossShipPosition.y + 28;

	otherCollisionVector[7].x = bossShipPosition.x + 147;
	otherCollisionVector[7].y = bossShipPosition.y + 30;

	otherCollisionVector[8].x = bossShipPosition.x + 153;
	otherCollisionVector[8].y = bossShipPosition.y + 32;

	otherCollisionVector[9].x = bossShipPosition.x + 157;
	otherCollisionVector[9].y = bossShipPosition.y + 34;

	otherCollisionVector[10].x = bossShipPosition.x + 161;
	otherCollisionVector[10].y = bossShipPosition.y + 36;

	otherCollisionVector[11].x = bossShipPosition.x + 164;
	otherCollisionVector[11].y = bossShipPosition.y + 38;

	otherCollisionVector[12].x = bossShipPosition.x + 166;
	otherCollisionVector[12].y = bossShipPosition.y + 40;

	otherCollisionVector[13].x = bossShipPosition.x + 168;
	otherCollisionVector[13].y = bossShipPosition.y + 42;

	otherCollisionVector[14].x = bossShipPosition.x + 170;
	otherCollisionVector[14].y = bossShipPosition.y + 46;

	otherCollisionVector[15].x = bossShipPosition.x + 172;
	otherCollisionVector[15].y = bossShipPosition.y + 50;

	otherCollisionVector[16].x = bossShipPosition.x + 173;
	otherCollisionVector[16].y = bossShipPosition.y + 54;

	otherCollisionVector[17].x = bossShipPosition.x + 99;
	otherCollisionVector[17].y = bossShipPosition.y + 99;

	otherCollisionVector[18].x = bossShipPosition.x + 173;
	otherCollisionVector[18].y = bossShipPosition.y + 445;

	otherCollisionVector[19].x = bossShipPosition.x + 172;
	otherCollisionVector[19].y = bossShipPosition.y + 449;

	otherCollisionVector[20].x = bossShipPosition.x + 170;
	otherCollisionVector[20].y = bossShipPosition.y + 453;

	otherCollisionVector[21].x = bossShipPosition.x + 168;
	otherCollisionVector[21].y = bossShipPosition.y + 455;

	otherCollisionVector[22].x = bossShipPosition.x + 166;
	otherCollisionVector[22].y = bossShipPosition.y + 457;

	otherCollisionVector[23].x = bossShipPosition.x + 164;
	otherCollisionVector[23].y = bossShipPosition.y + 459;

	otherCollisionVector[24].x = bossShipPosition.x + 161;
	otherCollisionVector[24].y = bossShipPosition.y + 461;

	otherCollisionVector[25].x = bossShipPosition.x + 157;
	otherCollisionVector[25].y = bossShipPosition.y + 463;

	otherCollisionVector[26].x = bossShipPosition.x + 153;
	otherCollisionVector[26].y = bossShipPosition.y + 465;

	otherCollisionVector[27].x = bossShipPosition.x + 147;
	otherCollisionVector[27].y = bossShipPosition.y + 467;

	otherCollisionVector[28].x = bossShipPosition.x + 141;
	otherCollisionVector[28].y = bossShipPosition.y + 469;

	otherCollisionVector[29].x = bossShipPosition.x + 134;
	otherCollisionVector[29].y = bossShipPosition.y + 471;

	otherCollisionVector[30].x = bossShipPosition.x + 126;
	otherCollisionVector[30].y = bossShipPosition.y + 473;

	otherCollisionVector[31].x = bossShipPosition.x + 118;
	otherCollisionVector[31].y = bossShipPosition.y + 475;

	otherCollisionVector[32].x = bossShipPosition.x + 108;
	otherCollisionVector[32].y = bossShipPosition.y + 477;

	otherCollisionVector[33].x = bossShipPosition.x + 98;
	otherCollisionVector[33].y = bossShipPosition.y + 479;

	otherCollisionVector[34].x = bossShipPosition.x + 93;
	otherCollisionVector[34].y = bossShipPosition.y + 481;


	//otherCollisionVector[14].x = bossShipPosition.x + 170;
	//otherCollisionVector[14].y = bossShipPosition.y + 46;

	//otherCollisionVector[14].x = bossShipPosition.x + 170;
	//otherCollisionVector[14].y = bossShipPosition.y + 46;
}

void PlayerShip::freePlayerTexture()
{
	if (mPlayerTexture != nullptr)
	{
		SDL_DestroyTexture(mPlayerTexture);

		//delete mPlayerTexture;
		mPlayerTexture = nullptr;
		m_Dimensions.x = 0; 
		m_Dimensions.y = 0; 

		mColliders.w = 0;
		mColliders.h = 0;
	}

}

bool PlayerShip::loadCannon(std::string path, SDL_Renderer* gRenderer)

{
	//initialization flag
	bool success = true;

	SDL_Texture* newTexture = NULL;

	//load image at specified path 
	SDL_Surface* loadedBossSurface = IMG_Load(path.c_str());
	if (loadedBossSurface == NULL)
	{
		printf("Unable to load image %s\n", SDL_GetError(), IMG_GetError());
	}
	else
	{
		//color key image 
		SDL_SetColorKey(loadedBossSurface, SDL_TRUE, SDL_MapRGBA(loadedBossSurface->format, 0, 0xFF, 0xFF, 0xFF));

		//create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedBossSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s!, SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//get image dimensions 
			m_CannonDimensions.x = loadedBossSurface->w;
			m_CannonDimensions.y = loadedBossSurface->h;
		}

		//get rid of old loaded surface 
		SDL_FreeSurface(loadedBossSurface);
	}
	mCannonTexture = newTexture;
	return mCannonTexture != NULL;

}


void PlayerShip::drawCannon(glm::vec2 cannonPosition, SDL_Rect* clip, SDL_Renderer* gRenderer)
{


	//Set rendering space and render to screen
	SDL_Rect renderQuad = { cannonPosition.x, cannonPosition.y, m_CannonDimensions.x, m_CannonDimensions.y };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mCannonTexture, clip, &renderQuad, NULL, NULL, SDL_FLIP_NONE);



}

void PlayerShip::AddWeapon(Weapon* weapon)
{
	mPlayerWeapon.push_back(weapon);

	if (mCurrentWeaponIndex == -1)
	{
		mCurrentWeaponIndex = 0; 
	}

}