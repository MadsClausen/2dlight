#ifndef __GFX_HPP__
#define __GFX_HPP__

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <math/math.hpp>

namespace gfx
{
	struct game_window_t
	{
		SDL_Window *sdl_window;
		SDL_GLContext sdl_context;
		int w, h;
		char fullscreen;
		char *title;
		Uint32 sdl_flags;
	};

	int init();
	int destroy();

	// create an empty window and set it up for rendering (with OpenGL)
	int create_window(game_window_t *win);

	// destroy window
	void destroy_window(game_window_t *win);

	// clear screen
	void set_clear_color(math::vec4f color); // calls glClearColor()
	void clear(); // calls glClear()

	// swaps buffers, drawing backbuffer to window
	void flip(game_window_t *win);
};

#endif