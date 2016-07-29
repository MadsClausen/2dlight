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

	game_window_t::game_window_t() {}
	game_window_t::~game_window_t() {}

	char game_window_t::put_scene(scene_t *s)
	{
		/*
		// if(s->_parent_win != this) { printf("SCENE DOES NOT BELONG TO WINDOW\n"); return -1; }

		// begin texture mapping
		glBindFramebuffer(GL_FRAMEBUFFER_EXT | GL_FRAMEBUFFER, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, s->_out_tex);

		printf("tex: %u\n", s->_out_tex);

		// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glViewport(0, 0, 800, 600);
		glBegin(GL_QUADS);
        glNormal3d(0.0f, 0.0f, 1.0f);
	        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);    // top left
	        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 600.0f);     // bottom left
	        glTexCoord2f(1.0f, 1.0f); glVertex2f(800.0f, 600.0f);    // bottom right
	        glTexCoord2f(1.0f, 0.0f); glVertex2f(800.0f, 0.0f);   // top right
	    glEnd();
	
	    printf("put!\n");
	    */
	}
};