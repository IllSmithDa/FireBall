#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}



void InputManager::pressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	m_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	m_keyMap[keyID] = false;
}

void InputManager::setMouseCoords(float x, float y) {
	m_mouseCoords.x = x;
	m_mouseCoords.y = y;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = m_keyMap.find(keyID);
	if (it != m_keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool InputManager::isKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we will look for the key manually and if it finds the key, 
	// it wil return to value associated with the key. Otherwise it will return false. 
	auto it = m_keyMap.find(keyID);

	// This means it found key and did not reach the end of the map
	if (it != m_keyMap.end()) {

		// Found the key and return the value associated with the key. 
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}