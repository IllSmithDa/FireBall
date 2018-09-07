#pragma once
#include <string>
#include <glm\glm.hpp>
#include <vector>

#include "Cannon.h"

class Weapon
{
public:
	Weapon(std::string mGunName);
	~Weapon();

	void update(/*bool isMousedown,*/ glm::vec2 &mPosition, int mDirection, std::vector<Cannon> & mCannon );
	void fireWeapon(int mDirection, const glm::vec2 &position, std::vector<Cannon> &mCannon);

private:

	std::string mGunName;
};

