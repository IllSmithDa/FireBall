#include "Sprite.h"

//Walking animation
const int WALKING_ANIMATION_FRAMES = 1;
//SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

Sprite::Sprite()
{

	
	//Initialize the offsets
	mPosParticleX = 15;
	mPosParticleY = 142;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;


	mPosShipX = 400;
	mPosShipY = 300;
	
	mPlayerShip.x = 400;
	mPlayerShip.y = 300; 

	mShipCollision.w = SPRITE_WIDTH;
	mShipCollision.h = SPRITE_HEIGHT;


	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i] = new ParticleEngine(mPosParticleX, mPosParticleY, gRedTexture, gGreenTexture, gBlueTexture);
	}
	
}


Sprite::~Sprite()
{
}


bool Sprite::loadSpriteFromFile(std::string path, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer)
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
			mWidth = loadedSurface->w ;
			mHeight = loadedSurface->h ;
		}

		//get rid of old loaded surface 
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;

	return mTexture != NULL;

}


int Sprite::getWidth()
{
	return mWidth;
}

int Sprite::getHeight()
{
	return mHeight;
}


void Sprite::eventHandler(SDL_Event &e)
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
				//m_moveState = PlayerMoveState::STANDING;
			}
			break;
		case SDLK_s:
			mVelY += SPRITE_VEL;

			if (mVelX == 0)
			{
				//m_moveState = PlayerMoveState::STANDING;

			}
			break;
		case SDLK_a: 
			mVelX -= SPRITE_VEL;
			//m_moveState = PlayerMoveState::RUNNING;

			if (mflip == SDL_FLIP_NONE)
			{
				mflip = SDL_FLIP_NONE;
			}
			else if (mflip == SDL_FLIP_HORIZONTAL)
			{
				mflip = SDL_FLIP_NONE;
			}

			break;
		case SDLK_d:
			mVelX += SPRITE_VEL; 
			//m_moveState = PlayerMoveState::RUNNING;

			if (mflip == SDL_FLIP_NONE)
			{
				mflip = SDL_FLIP_HORIZONTAL;
			}
			else if (mflip == SDL_FLIP_HORIZONTAL)
			{
				mflip = SDL_FLIP_HORIZONTAL;
			}

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
			//	m_moveState = PlayerMoveState::STANDING;
			}
			break;
		case SDLK_d:
			mVelX -= SPRITE_VEL;

			if (mVelX == 0)
			{
			
		//	m_moveState = PlayerMoveState::STANDING;
			}
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


}


void Sprite::loadSprite(SDL_Renderer* gRenderer)
{

	/*
	//gSpriteFigure.loadSmallTextureFile("Assets/foo2.png", gRenderer);
	//gSpriteFigure.loadSmallTextureFile("Assets/blue_ninja.png", gRenderer);
	//gSpriteFigure.loadSmallTextureFile("Assets/ship3.png", gRenderer);
	gSpriteFigure.loadSmallTextureFile("Assets/ship3.png", gRenderer);
	
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 64;
	gSpriteClips[0].w = 64;
	gSpriteClips[0].h = 64;
	
	*/
	/*
	//Create the necessary SDL_Rects
	mShipCollision.resize(3);
	//mSmallShipCollision.resize(3);


	//intialize player ship 
//	mSmallShipCollision[0].h = 9;
//	mSmallShipCollision[0].w = 23;

//	mSmallShipCollision[1].h = 36;
//	mSmallShipCollision[1].w = 60;


	//mSmallShipCollision[2].h = 9;
//	mSmallShipCollision[2].w = 23;

	//Initialize the collision boxes' width and height
	mShipCollision[0].w = 323;
	mShipCollision[0].h = 83;

	mShipCollision[1].w = 300;
	mShipCollision[1].h = 300;

	mShipCollision[2].w = 323;
	mShipCollision[2].h = 83;

	mShipCollision[3].w = 323;
	mShipCollision[3].h = 83;

	mShipCollision[4].w = 39;
	mShipCollision[4].h = 262;

	*/
	//Initialize colliders relative to position
//	shiftColliders();

}



void Sprite::loadParticles(SDL_Renderer* gRenderer)
{


	//Load red texture
	if (!gRedTexture.loadSmallTextureFile("Assets/orange.bmp", gRenderer))
	{
		printf("Failed to load red texture!\n");
		
	}

	//Load green texture
	if (!gGreenTexture.loadSmallTextureFile("Assets/orange.bmp", gRenderer))
	{
		printf("Failed to load green texture!\n");
		
	}

	//Load blue texture
	if (!gBlueTexture.loadSmallTextureFile("Assets/orange.bmp", gRenderer))
	{
		printf("Failed to load blue texture!\n");
		
	}

	//Load shimmer texture
	if (!gShimmerTexture.loadSmallTextureFile("Assets/shimmer.bmp", gRenderer))
	{
		printf("Failed to load shimmer texture!\n");
		
	}

	//Set texture transparency
	gRedTexture.setAlpha(155);
	gGreenTexture.setAlpha(155);
	gBlueTexture.setAlpha(155);
	gShimmerTexture.setAlpha(155);
}


void Sprite::move(int SCREEN_WIDTH, int SCREEN_HEIGHT, glm::vec2 shipPosition)
{
	//Move the particle left or right
	mPosParticleX += mVelX;


	//If the particle went too far to the left or right
	if ((mPosParticleX < 15) || (mPosParticleX + SPRITE_WIDTH > SCREEN_WIDTH - (SPRITE_WIDTH * 4.6)) )
	{
		//Move back
		mPosParticleX -= mVelX;
	}

	//Move the dot up or down
	mPosParticleY += mVelY;
	
	//If the dot went too far up or down
	if ((mPosParticleY < SPRITE_HEIGHT * 2.644341) || (mPosParticleY + SPRITE_HEIGHT > SCREEN_HEIGHT - (SPRITE_HEIGHT * 2)))
	{
		//Move back
		mPosParticleY -= mVelY;
	}


	//Move the ship left or right
	mPlayerShip.x += mVelX;


	//If the player ship went too far to the left or right
	if ((mPlayerShip.x < 0) || (mPlayerShip.x  > SCREEN_WIDTH - (SPRITE_WIDTH ) ))
	{
		//Move back
		mPlayerShip.x -= mVelX;

	}

	//Move the dot up or down
	mPlayerShip.y += mVelY;


	//If the dot went too far up or down
	if ((mPlayerShip.y < 0) || (mPlayerShip.y > SCREEN_HEIGHT - (SPRITE_HEIGHT) ))
	{
		//Move back
		mPlayerShip.y -= mVelY;

	
	}

	//Define the gravity that the world will use using the Box2D's vector class
	b2Vec2 gravity(0.0f, -9.0f);


	//set up the world and pass in the gravity 
	m_world = std::make_unique<b2World>(gravity);

	//Define the box
	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;

	//set position of body or box 
	bodyDef.position.Set(0, 0);

	//bodyDef.angle = 0; //set the starting angle


	m_body = m_world->CreateBody(&bodyDef);

	//create the shape of the box 
	b2Vec2 vertices[3];
	vertices[0].Set(1.0f, -1.0f);
	vertices[1].Set(2.0f, 0.0f);
	vertices[2].Set(0.0f, -2.0f);
	int32 count = 3;
	b2PolygonShape polygon;
	polygon.Set(vertices, count);
	

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &polygon;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 0.3f;

	m_body->CreateFixture(&boxFixtureDef);


	//Create the actual body using the definitions created above
	//m_body = m_world.get()->CreateBody(&bodyDef);

	/*
	//create the fixture 
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;

	//set density to 1 as dynamic object cannot have a density of 0
	fixtureDef.density = 1.0f;

	//create the friction 
	fixtureDef.friction = 0.3f;

	//store the friction pointer and create it using the world
	m_fixture = m_body->CreateFixture(&fixtureDef);

	*/

	
	//circle collision
	
	//Miminin distance before there is a collision 
	const float MIN_DISTANCE = (SPRITE_WIDTH/2) + (200);

	//measures the center position of one agent potentially in collision
	glm::vec2 centerPosA = mPlayerShip + glm::vec2(SPRITE_WIDTH/2);

	//measure the other agent's center position potentially in collsion
	glm::vec2 centerPosB = shipPosition + glm::vec2(475 / 2);

	//Creates the distance vector between the two agents
	glm::vec2 distVec = centerPosA - centerPosB;

	//Measure the length of the distance vector; the function will calculate 
	// the distance for us using A^2 = B^2 + C^2
	float distance = glm::length(distVec);

	//Depth of the collision 
	float collisionDepth = MIN_DISTANCE - distance;

	// IF the minimum required distance for colllision or MIN_DISTANCE (retpresented by collisionDepth > 0) is greater 
	// than the actual distance, then there is a collision leading to the following funtions in the if statemensts. 
	if (collisionDepth > 0) {

		//pushing out by the distVec is pushing out far to much. Instead we want to push them 
		//out by the direction o the distVec * collsion depth or the total length of the collision 
		//depth. This is like a unit vector length of one * collsion depth will give the vector 
		//length of collision depth
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;


		//Push both agents out by the length of their collision by equal part by half so 
		//you divide by 2 
		mPlayerShip += collisionDepthVec / 2.0f;

		shipPosition -= collisionDepthVec / 2.0f;




	}
	
}



void Sprite::renderSprite(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle,  SDL_Point* center, SDL_RendererFlip flip )
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)	
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	
	
}



void Sprite::renderWithAngle(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip )
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);



}

void Sprite::render(SDL_Renderer* gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int animateframe, SDL_Rect* clip)
{
	/*
	//Show particles on top of dot
	//renderParticles(gRenderer);

	//numFrames = animateframe;

	if (m_moveState == PlayerMoveState::RUNNING)
	{ 


	int frame = 0;
	//Render current frame
//	SDL_Rect* currentClip = &gSpriteClips[animateframe / 10];

	//renderSprite(mPosShipX, mPosShipY, gRenderer, currentClip);
	gSpriteFigure.renderWithAngle(mPlayerShip.x, mPlayerShip.y, gRenderer, clip, mflip);
	}
	else if(m_moveState == PlayerMoveState::STANDING)
	{
		//SDL_Rect* currentClip  = &gSpriteClips[0];

		//renderSprite(mPosShipX, mPosShipY, gRenderer, currentClip);
	//	gSpriteFigure.renderWithAngle(mPlayerShip.x, mPlayerShip.y, gRenderer, currentClip, mflip);
	}

	//Go to next frame
	//++animateframe;
	//Update screen

	//if (animateframe / 10 >= 4)
	//{
//		animateframe = 0;
//	}

*

}

void Sprite::destroyTexture()
{

	SDL_GL_UnbindTexture(mTexture);
}

void Sprite::update()
{

	/*
	m_position.y = 0;
	m_position.x = 0;

	if (m_inputManager->isKeyPressed(SDLK_w)) {

		m_position.y += m_speed;
	}
	else if (m_inputManager->isKeyPressed(SDLK_s)) {

		m_position.y -= m_speed;
	}
	if (m_inputManager->isKeyPressed(SDLK_a)) {

		m_moveState = PlayerMoveState::RUNNING;


		m_position.x -= m_speed;
	}
	else if (m_inputManager->isKeyPressed(SDLK_d)) {

		m_moveState = PlayerMoveState::RUNNING;
		m_position.x += m_speed;
	}
	*/

}



void Sprite::renderParticles(SDL_Renderer* gRenderer)
{
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		
		//Delete and replace dead particles
		if (particles[i]->isDead())
		{
			delete particles[i];
			particles[i] = new ParticleEngine(mPosParticleX, mPosParticleY, gRedTexture, gGreenTexture, gBlueTexture);
		}
		
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{

		particles[i]->render(gRenderer, gShimmerTexture);
		
		
	}
}

/*
void Sprite::shiftColliders() 

{
	//The row offset
	int r = 0;

	//Go through the dot's collision boxes
	for (int set = 0; set < mShipCollision.size(); ++set)
	{
		//Center the collision box
		mShipCollision[set].x = mPosShipX + (SPRITE_WIDTH - mShipCollision[set].w) / 2;

		//Set the collision box at its row offset
		mShipCollision[set].y = mPosShipY + r;

		//Move the row offset down the height of the collision box
		r += mShipCollision[set].h;
	}

}

*/
bool Sprite::checkCollision(SDL_Rect a, SDL_Rect b)
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

	//If none of the sides from A are outside B
	return true;
}


void Sprite::setTexture()
{


}

void Sprite::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Sprite::showImage(SDL_Renderer* gRenderer)
{

	//Show image1
	//mSpriteTexture.renderWithAngle(mPosX, mPosY, gRenderer);
}

void Sprite::showShimmerTexture(SDL_Renderer* gRenderer)
{
	//gShimmerTexture.renderWithAngle(mPosX, mPosY, gRenderer);
}

void Sprite::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}