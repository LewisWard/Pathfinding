// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include <iostream>
#include <stdint.h>
#include "SDL\SDL.h"
#include "SDL\SDL_opengl.h"
#include "Vec2.h"

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
	inline SDL_Window* window()
	{ return m_win; }

	/// \brief get the width of the window
	/// \return int
	inline int width()
	{ return m_width; }

	/// \brief get the height of the window
	/// \return int
	inline int height()
	{ return m_height; }

private:
	SDL_Window* m_win; ///< SDL Window
	int m_xPos; ///< X position
	int m_yPos; ///< Y position
	int m_width; ///< window width
	int m_height; ///< window height
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
	int eventQueue();

	/// \brief update the mouse event queue
	/// \return int event
	int mouseQueue();

	vec2& getMouseLocation() { return m_mouseLocation; };

private: 
	SDL_Event m_SDLEvent; ///< SDL event
	vec2 m_mouseLocation;
};
