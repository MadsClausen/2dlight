#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <stdio.h>
#include <GL/glew.h>

#include "math/math.hpp"

namespace gfx
{
	enum LIGHT_TYPE
	{
		LIGHT_TYPE_POINT,
		LIGHT_TYPE_SPOTLIGHT,
		LIGHT_TYPE_PLANE,
		NUM_LIGHT_TYPES
	};

	class scene_t;

	/*******************************
	**** MUST MATCH STRUCT IN SHADER
	********************************/
	struct shader_light_t
	{
		math::vec4f pos, color, dir /* for spotlight and plane */;
		float angle; // for spotlight
		int type; // point, spot, plane?
		float __align, __align2; // aling packing with vec4s
	};

	class light_t
	{
		private:
			scene_t *_parent_scene;

			char _scene_set, _changed;

		public:
			shader_light_t _shader_light_struct;
			math::vec3f pos, color, dir;
			float angle;

			LIGHT_TYPE type;

			light_t();
			light_t(math::vec3f p, math::vec3f c)
			{
				pos = p;
				color = c;
				type = LIGHT_TYPE_POINT;
			}

			~light_t();

			void set_parent_scene(scene_t *p)
			{
				_parent_scene = p;
				_scene_set = 1;
			}

			void update();

	};
};

#endif