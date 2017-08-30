// Author : Lewis Ward
// Date: 29/08/2017
#include "Texture.h"

Texture::Texture(const char* filename)
{
	// load texture from file
	m_surface = SDL_LoadBMP(filename);

	// check file loaded correctly
	if (!m_surface)
		std::cout << "Failed to load .bmp image :(" << std::endl;
}

Texture::~Texture()
{
	SDL_FreeSurface(m_surface);
	SDL_DestroyTexture(m_texture);
}

void Texture::createTexture(SDL_Renderer* renderer)
{
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
}
