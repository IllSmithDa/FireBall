#pragma once

#include <glm\glm.hpp>
#include <unordered_map>
class InputManager
{
public:
	InputManager();
	~InputManager();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(float x, float y);

	bool isKeyPressed(unsigned int keyID);

	bool InputManager::isKeyDown(unsigned int keyID);

	//getters
	glm::vec2 getMouseCoords() const { return m_mouseCoords; }



private:
	std::unordered_map<unsigned int, bool> m_keyMap;
	glm::vec2 m_mouseCoords;
};

