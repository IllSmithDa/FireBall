#pragma once

#include "vertex.h"
#include <vector>
#include <glm\glm.hpp>
#include <SDL\SDL.h>
#include <Box2D\Box2D.h>




class DebugRenderer
{
public:
	DebugRenderer();
	~DebugRenderer();

	void drawBox(const glm::vec4 &destRect,
		const ColorRGBA8 &color, float angle);

	struct DebugVertex {
		glm::vec2 position;

		ColorRGBA8 color;

	};

	//store indices inside a vector; GLuint allows for maximum amount of vertices allowing for 
	//drawing greater amount of objects in the world including boxes
	std::vector<GLuint> m_indices;

private:

	//used for index drawings which will prevent ducplcate points and vertices 
	//so it will save memory allocation by just drawing 4 lines rather than 6 vertices 
	//which usually makes up the square. Adds up when dealing with larger quantities of data 
	std::vector<DebugVertex> m_verts;
};
