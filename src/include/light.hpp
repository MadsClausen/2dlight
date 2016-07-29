#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <GL/glew.h>

#include "math/math.hpp"

namespace gfx
{
	class scene_t;

	class light_t
	{
		private:
			math::vec2f _pos;
			float _radius;
			float _a, _b, _c; // for determining how the light develops over distance
			scene_t *_parent_scene;

			GLuint _base_tex, _final_tex;

			char _scene_set;

		public:
			light_t();
			~light_t();

			void generate_base_texture(); // base texture to be used when generating shadows
			GLuint generate_final_texture(); // generate texture with shadows

			void set_parent_scene(scene_t *p)
			{
				_parent_scene = p;
				_scene_set = 1;
			}
	};
}

#endif