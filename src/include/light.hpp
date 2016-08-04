#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <GL/glew.h>

#include "math/math.hpp"

namespace gfx
{
	class scene_t;

	/*******************************
	**** MUST MATCH STRUCT IN SHADER
	********************************/
	struct shader_light_t
	{
		math::vec3f pos, color, dir /* for spotlight and plane */;
		float angle; // for spotlight
		int type; // point, spot, plane?
	};

	class light_t
	{
		private:
			float _a, _b, _c; // for determining how the light develops over distance
			scene_t *_parent_scene;

			shader_light_t _shader_light;

			char _scene_set;

		public:
			math::vec3f pos, color;

			light_t();
			light_t(math::vec3f p, math::vec3f c)
			{
				pos = p;
				color = c;
			}

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