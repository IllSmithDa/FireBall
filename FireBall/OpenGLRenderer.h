#pragma once
#include <string>
#include <IL\il.h>
#include <stdio.h>
#include <GL\freeglut.h>
#include <GL\GLU.h>
#include <GL\GL.h>

class OpenGLRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	bool loadTextureFromFile(std::string path);

	bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);

	void freeTexture();

	void render(GLfloat x, GLfloat y);

	GLuint getTextureID();
	GLuint textureWidth();
	GLuint textureHeight();

private:

	//Texture name
	GLuint mTextureID;

	//Texture dimensions
	GLuint mTextureWidth;
	GLuint mTextureHeight;
};

