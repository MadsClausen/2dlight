#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <vector>

#include <GL/glew.h>

#include "mesh.hpp"

namespace gfx
{
	class game_window_t;

	// SCENE RENDERS TO TEXTURE
	class scene_t
	{
		friend class game_window_t;

		private:
			std::vector<mesh_t *> _objects;
			// std::vector<light_t> _lights;
			GLuint _fbuf, _out_tex, _depth_rb;
			GLenum _drawbufs[1];
			game_window_t *_parent_win;

			int _w, _h;

		public:
			scene_t();
			~scene_t();

			void render();

			char set_parent_window(game_window_t *win);

			void add_mesh(mesh_t *o);
	};
};

#endif