#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <vector>

#include <GL/glew.h>

#include "light.hpp"
#include "mesh.hpp"
#include "shader.hpp"

#define MAX_LIGHTS 20
#define LIGHT_DATA_BINDING_POINT 1

namespace gfx
{
	class game_window_t;

	// SCENE RENDERS TO TEXTURE
	class scene_t
	{
		friend class game_window_t;

		private:
			std::vector<mesh_t *> _meshes;
			std::vector<shader_t *> _light_shaders; // shaders to send light data to
			light_t *_lights[MAX_LIGHTS];
			game_window_t *_parent_win;

			GLuint _light_data_buffer;
			unsigned int _num_lights;

		public:
			scene_t();
			~scene_t();

			void render();

			char set_parent_window(game_window_t *win) { _parent_win = win; };

			void add_mesh(mesh_t *o);

			void add_light_shader(shader_t *s);

			// returns 0 if max amount of lights is reached
			char add_light(light_t *l);
			void update_light_data();
	};
};

#endif