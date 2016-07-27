#include "gfx.hpp"

namespace gfx
{
	void set_clear_color(math::vec4f color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void flip(game_window_t *win)
	{
		SDL_GL_SwapWindow(win->sdl_window);
	}
};