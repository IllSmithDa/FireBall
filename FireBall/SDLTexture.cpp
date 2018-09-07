#include "SDLTexture.h"



SDLTexture::SDLTexture()
{

	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}


SDLTexture::~SDLTexture()
{
}

bool SDLTexture::initGRenderer(SDL_Window* gWindow)
{
	bool success = true; 
	return success; 
}


bool SDLTexture::loadSmallTextureFile(std::string path, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool SDLTexture::loadfromFile(std::string path, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer)
{
	//initialization flag
	bool success = true;

	SDL_Texture* newTexture = NULL;

	//load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s\n", SDL_GetError(), IMG_GetError());
	}
	else
	{
		//color key image 
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGBA(loadedSurface->format, 0, 0xFF, 0xFF, 0xFF));

		//create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s!, SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//get image dimensions 
			mWidth = SCREEN_WIDTH;
			mHeight = SCREEN_HEIGHT;
		}

		//get rid of old loaded surface 
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;

	return mTexture != NULL;


}

void SDLTexture::render(int x, int y, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void SDLTexture::renderBackground(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void SDLTexture::renderWithAngle(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip,  double angle, SDL_Point* center)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

}
void SDLTexture::clipRender(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 0, 100, 100, 100 };

	
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	if (clip == NULL)
	{
		printf("Warning clip is not working");
	}
	
	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void SDLTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int SDLTexture::getWidth()
{
	return mWidth;
}

int SDLTexture::getHeight()
{
	return mHeight;
}


void SDLTexture::free()
{
	//free texture if it exists 
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

