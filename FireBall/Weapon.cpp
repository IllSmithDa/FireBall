#include "Weapon.h"



Weapon::Weapon(std::string mGunName): mGunName(mGunName)
{
}


Weapon::~Weapon()
{
}


void Weapon::update(/*bool isMousedown,*/ glm::vec2 &mPosition, int mDirection, std::vector<Cannon> & mCannon)
{
	

		fireWeapon(mDirection, mPosition, mCannon);
	
}

void Weapon::fireWeapon(int mDirection, const glm::vec2 &position, std::vector<Cannon> &mCannon)
{

	mCannon.emplace_back(position, 10.0f, mDirection);
}