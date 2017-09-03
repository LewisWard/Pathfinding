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
	XPos = 0;
	YPos = 30;
	Width = 600;
	Height = 600;

	// create SDL window
	TheWindow = SDL_CreateWindow("Lewis Ward's AI", XPos, YPos, Width, Height, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	// destory windown
	SDL_DestroyWindow(TheWindow);
}


Events::Events()
{

}

Events::~Events()
{

}

int Events::EventQueue()
{
	while (SDL_PollEvent(&SDLEvent))
	{
		switch (SDLEvent.type)
		{
			// user clicked on the close button
		case SDL_QUIT:
			return 100;
			break;
			// user has pressed the 'Esc' W/A/S/D key
		case SDL_KEYDOWN:
			if (SDLK_ESCAPE == SDLEvent.key.keysym.sym)
				return 100;
			if (SDLK_w == SDLEvent.key.keysym.sym)
				return 1;
			if (SDLK_a == SDLEvent.key.keysym.sym)
				return 2;
			if (SDLK_s == SDLEvent.key.keysym.sym)
				return 3;
			if (SDLK_d == SDLEvent.key.keysym.sym)
				return 4;
			break;
		default: return -1; break; // no event
		}
	}
}

int Events::MouseQueue()
{
		switch (SDLEvent.type)
		{
		// mouse button pressed
		case SDL_MOUSEBUTTONDOWN:
			if (SDL_BUTTON_LEFT == SDLEvent.button.button)
				return 0;
			if (SDL_BUTTON_MIDDLE == SDLEvent.button.button)
				return 1;
			if (SDL_BUTTON_RIGHT == SDLEvent.button.button)
				return 2;
			break;
		// mouse moved
		case SDL_MOUSEMOTION:
			{
				// update mouse position
				MouseLocation.X = SDLEvent.motion.x;
				MouseLocation.Y = SDLEvent.motion.y;
			}
			break;
			default: return -1; break; // no event
		}

		return -1;
}
