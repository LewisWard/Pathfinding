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
	Texture(const char* filename);

	/// \brief Destr
	~Texture();

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	void createTexture(SDL_Renderer* renderer);

	/// \brief get the surface
	/// \return SDL_Surface* surface
	inline SDL_Surface* surface()
	{ return m_surface; }

	/// \brief get the texture
	/// \return SDL_Texture* texture
	inline SDL_Texture* texture()
	{ return m_texture; }

private:
	SDL_Surface* m_surface = nullptr; ///< surface
	SDL_Texture* m_texture = nullptr; ///< texture
};
