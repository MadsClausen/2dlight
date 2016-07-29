#include "gfx.hpp"

namespace gfx
{
	int init()
	{
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			return -1;
		}

		return 0;
	}

	int destroy()
	{
		SDL_Quit();

		return 0;
	}

	int create_window(game_window_t *win)
	{
		win->sdl_window = SDL_CreateWindow(win->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win->w, win->h, SDL_WINDOW_OPENGL);

		if(win->sdl_window == 0)
			return -1;

		// enable OpenGL
		win->sdl_context = SDL_GL_CreateContext(win->sdl_window);

		// SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 	8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 	8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 	8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK)
		{
			printf("ERROR INITIALISING GLEW\n");
			return -1;
		}

		return 0;
	}

	void destroy_window(game_window_t *win)
	{
		SDL_GL_DeleteContext(win->sdl_context);
		SDL_DestroyWindow(win->sdl_window);
	}
}