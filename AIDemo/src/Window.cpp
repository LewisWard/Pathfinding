// Author : Lewis Ward
// Date: 29/08/2017
#include "Window.h"

// http://msdn.microsoft.com/en-gb/library/windows/desktop/ms644905(v=vs.85).aspx
// gobal variables for dt
uint64_t g_start = 0, g_last = 0, g_new = 0;
float g_CPS;

void initTimerDT()
{
	// get the current performance-counter frequency
	QueryPerformanceFrequency((LARGE_INTEGER*)&g_start);
	// compute Count Per Seconds (CPS)
	g_CPS = 1.0f / g_start;

	// setup previous time
	QueryPerformanceCounter((LARGE_INTEGER*)&g_last);
}

float updateTimerDT()
{
	// get the current frequency
	QueryPerformanceCounter((LARGE_INTEGER*)&g_new);
	// compute the DT
	float dt = (g_new - g_last) * g_CPS;
	// update last time value with new
	g_last = g_new;
	// return dt
	return dt;
}

Window::Window()
{
	// initialisation of SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// initialisation failed
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// setup delta time
	initTimerDT();

	// set window X and Y positions and defalut screen position
	m_xPos = 0;
	m_yPos = 30;
	m_width = 600;
	m_height = 600;

	// create SDL window
	m_win = SDL_CreateWindow("Lewis Ward's AI", m_xPos, m_yPos, m_width, m_height, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	// destory windown
	SDL_DestroyWindow(m_win);
}


Events::Events()
{

}

Events::~Events()
{

}

int Events::eventQueue()
{
	while (SDL_PollEvent(&m_SDLEvent))
	{
		switch (m_SDLEvent.type)
		{
			// user clicked on the close button
		case SDL_QUIT:
			return 100;
			break;
			// user has pressed the 'Esc' W/A/S/D key
		case SDL_KEYDOWN:
			if (SDLK_ESCAPE == m_SDLEvent.key.keysym.sym)
				return 100;
			if (SDLK_w == m_SDLEvent.key.keysym.sym)
				return 1;
			if (SDLK_a == m_SDLEvent.key.keysym.sym)
				return 2;
			if (SDLK_s == m_SDLEvent.key.keysym.sym)
				return 3;
			if (SDLK_d == m_SDLEvent.key.keysym.sym)
				return 4;
			break;
		default: return -1; break; // no event
		}
	}
}

int Events::mouseQueue()
{
		switch (m_SDLEvent.type)
		{
		// mouse button pressed
		case SDL_MOUSEBUTTONDOWN:
			if (SDL_BUTTON_LEFT == m_SDLEvent.button.button)
				return 0;
			if (SDL_BUTTON_MIDDLE == m_SDLEvent.button.button)
				return 1;
			if (SDL_BUTTON_RIGHT == m_SDLEvent.button.button)
				return 2;
			break;
		// mouse moved
		case SDL_MOUSEMOTION:
			{
				// update mouse position
				m_mouseLocation.x = m_SDLEvent.motion.x;
				m_mouseLocation.y = m_SDLEvent.motion.y;
			}
			break;
			default: return -1; break; // no event
		}
}
