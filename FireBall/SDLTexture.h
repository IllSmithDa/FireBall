#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

class SDLTexture
{
public:
	SDLTexture();
	~SDLTexture();

	//The window renderer
	//SDL_Renderer* gRenderer;

	//The actual hardware texture
	SDL_Texture* mTexture;

	void clipRender(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer);

	//uploading texture 
	bool loadfromFile(std::string path, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer);

	//intializing window renderer
	bool initGRenderer(SDL_Window* gWindow);

	//draw background 
	void renderBackground(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer);

	//rendering texture
	void render(int x, int y, SDL_Renderer* gRenderer);

	//rendering with angle
	void renderWithAngle(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle = 0.0, SDL_Point* center = NULL);

	//set alpha 
	void setAlpha(Uint8 alpha);

	//load small textures
	bool loadSmallTextureFile(std::string path, SDL_Renderer* gRenderer);

	//freeing texture
	void free();

	//closing program 
	void close(SDL_Renderer* gRenderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	int mWidth; 
	int mHeight; 
};

