#include "PlayerCapsule.h"



PlayerCapsule::PlayerCapsule()
{
}


PlayerCapsule::~PlayerCapsule()
{
}

void PlayerCapsule::init(b2World* world, const glm::vec2 PlayerShipPosition, const glm::vec2 &PlayerShipDimensions,
	float PlayerShipDensity, float PlayerShipFriction, bool PlayerShipRotation)
{

	m_PlayerShipDimensions = m_PlayerShipDimensions;

	//These entire lines of code set up the first fixture 
	//Define the box
	b2BodyDef bodyDef;

	//Will be a dynamic body 
	bodyDef.type = b2_dynamicBody;

	//set position of body or box 
	bodyDef.position.Set(PlayerShipPosition.x, PlayerShipPosition.y);

	//set fixed rotation so player won't rotate randomly
	bodyDef.fixedRotation = PlayerShipRotation;

	//Create the actual body using the definitions created above
	m_PlayerShipBody = world->CreateBody(&bodyDef);


	//create the shape of the box 
	b2PolygonShape boxShape;

	//set up box shape and then shrink it by subtracting by dimension.x/ 2
	boxShape.SetAsBox(PlayerShipDimensions.x / 2.0f, (PlayerShipDimensions.y - PlayerShipDimensions.x) / 2.0f);

	//create the fixture 
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;

	//set density to 1 as dynamic object cannot have a density of 0
	fixtureDef.density = PlayerShipDensity;

	//create the friction 
	fixtureDef.friction = PlayerShipDensity;

	//store the friction pointer and create it using the world
	m_PlayerShipFixture[0] = m_PlayerShipBody->CreateFixture(&fixtureDef);

}

void PlayerCapsule::destroy(b2World* world)
{
	if (m_PlayerShipBody)
	{
		//destory player ship body
		world->DestroyBody(m_PlayerShipBody);
		m_PlayerShipBody = nullptr;
	}

}

