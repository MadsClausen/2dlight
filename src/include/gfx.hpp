#ifndef __GFX_HPP__
#define __GFX_HPP__

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <math/math.hpp>

#include "scene.hpp"

namespace gfx
{
	class game_window_t
	{
		public:
			SDL_Window *sdl_window;
			SDL_GLContext sdl_context;
			int w, h;
			char fullscreen;
			char *title;
			Uint32 sdl_flags;

			game_window_t();
			~game_window_t();

			// return -1 if not good
			char put_scene(scene_t *s);
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