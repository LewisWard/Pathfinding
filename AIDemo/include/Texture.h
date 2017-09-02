// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Texture class
//----------------------------------------------------------------------------------------------------------------------
class Texture
{
public:
	/// \brief Constr
	/// \prama char* file name of texture
	Texture(const char* Filename);

	/// \brief Destr
	~Texture();

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	void CreateTexture(SDL_Renderer* Renderer);

	/// \brief get the surface
	/// \return SDL_Surface* surface
	inline SDL_Surface* GetSurface() { return Surface; }

	/// \brief get the texture
	/// \return SDL_Texture* texture
	inline SDL_Texture* GetTexture() { return TheTexture; }

private:
	SDL_Surface* Surface = nullptr;
	SDL_Texture* TheTexture = nullptr; 
};
