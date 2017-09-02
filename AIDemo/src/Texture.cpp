// Author : Lewis Ward
// Date: 29/08/2017
#include "Texture.h"

Texture::Texture(const char* Filename)
{
	// load texture from file
	Surface = SDL_LoadBMP(Filename);

	// check file loaded correctly
	if (!Surface)
		std::cout << "Failed to load .bmp image!" << std::endl;
}

Texture::~Texture()
{
	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(TheTexture);
}

void Texture::CreateTexture(SDL_Renderer* Renderer)
{
	TheTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
}
