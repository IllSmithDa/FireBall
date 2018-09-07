#pragma once

#include <Box2D\Box2D.h>
#include<glm\glm.hpp>

class PlayerCapsule
{
public:
	PlayerCapsule();
	~PlayerCapsule();


	void init(b2World* world, const glm::vec2 PlayerShipPosition, const glm::vec2 &PlayerShipDimensions,
		float PlayerShipDensity, float PlayerShipFriction, bool PlayerShipRotation);

	void destroy(b2World* world);

	//get dimensions, body and fixture of the Player Ship
	b2Body* getPlayerShipBody() { return m_PlayerShipBody; }
	b2Fixture* getPlayerShipFixture(int index) { return m_PlayerShipFixture[index]; }
	const glm::vec2 &getPlayerShipDimensions() { return m_PlayerShipDimensions; }

	

private:

	//The body of the ship 
	b2Body* m_PlayerShipBody; 

	b2Fixture* m_PlayerShipFixture[3]; 

	glm::vec2 m_PlayerShipDimensions; 
	


};

