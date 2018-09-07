
#include "DebugRenderer.h"



DebugRenderer::DebugRenderer()
{
}


DebugRenderer::~DebugRenderer()
{
}


//The function will be called to determine the angle from origin. This function is a standalone 
//and not mentioned in the header file 
glm::vec2 rotatePoint(const glm::vec2& pos, float angle) {

	//Trignometry formula for finding the angle of direction based 
	//on the point of origin
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}
void DebugRenderer::drawBox(const glm::vec4 &destRect,
	const ColorRGBA8 &color, float angle)
{


		//store the index of the first position of the first vertex that will be modified. 
		//This is the location of the first vertex that will be modified 
		int i = m_verts.size();

		//Use and fill up or m verts vectors and changes the size by adding 4 to it 
		m_verts.resize(m_verts.size() + 4);

		//Half dims stand for half the dimensions with z being width, and w being height and 
		//is better than calling push_back 4 times 
		glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		// Get points centered at origin. Use the four corners of the vertices 
		// includin top left(tl), top right (tr), bottom left(bl) and bottom right (br). 
		// HalfDims stand for half the width of the x and y, width and height directions. 
		// The negative and positive signs indicate direction
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		//set up position offset for setting center position
		glm::vec2 positionOffset(destRect.x, destRect.y);


		// Rotate the points using the already established 
		// vectors.We add the half dimensions because whenever 
		// whenever we treated the center of the sprite of origin, 
		// the covention of treating the topleft as the position and 
		// correct that by adding the half Dimensions. 
		m_verts[i].position = rotatePoint(tl, angle) + halfDims + positionOffset;
		m_verts[i + 1].position = rotatePoint(bl, angle) + halfDims + positionOffset;
		m_verts[i + 2].position = rotatePoint(br, angle) + halfDims + positionOffset;
		m_verts[i + 3].position = rotatePoint(tr, angle) + halfDims + positionOffset;

		//set the color 
		for (int j = i; j < i + 4; j++) {
			m_verts[j].color = color;
		}

		//setting up the indices and use reserve to internally make sure it store enough memory 
		//for it to push back these 8 vertices 
		m_indices.reserve(m_indices.size() + 8);

		//add indices using push_back to add these indices to the vertex struct above. This will draw 
		//this draws lines between i and i + 1
		m_indices.push_back(i);
		m_indices.push_back(i + 1);

		//this draws lines between i + 1 and i + 2
		m_indices.push_back(i + 1);
		m_indices.push_back(i + 2);

		//this draws lines between i + 2 and i + 3
		m_indices.push_back(i + 2);
		m_indices.push_back(i + 3);

		//this draws lines between i + 3 and i 
		m_indices.push_back(i + 3);
		m_indices.push_back(i);
}
