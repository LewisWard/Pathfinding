// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include <iostream>
#include <stdint.h>
#include "SDL\SDL.h"
#include "SDL\SDL_opengl.h"
#include "Vec2.h"
#include "Config.h"

/// \brief setup delta time
void initTimerDT();

/// \brief update delta time
/// \return delta time
float updateTimerDT();

class Window
{
public:
	/// \brief Constr
	Window();

	/// \brief Destr
	~Window();

	/// \brief get the SDL_Window pointer for this window
	/// \return SDL_Window*
	inline SDL_Window* GetWindow() { return TheWindow; }

	/// \brief get the width of the window
	/// \return int
	inline int GetWidth() { return Width; }

	/// \brief get the height of the window
	/// \return int
	inline int GetHeight() { return Height; }

private:
	SDL_Window* TheWindow; ///< SDL Window
	int XPos; ///< X position
	int YPos; ///< Y position
	int Width; ///< window width
	int Height; ///< window height
};

class Events
{
public:
	/// \brief Constr
	Events();

	/// \brief Destr
	~Events();

	/// \brief update the event queue (i.e which key has been pressed)
	/// \return int event
	int EventQueue();

	/// \brief update the mouse event queue
	/// \return int event
	int MouseQueue();

	Vec2& GetMouseLocation() { return MouseLocation; };

private: 
	SDL_Event SDLEvent;
	Vec2 MouseLocation;
};
