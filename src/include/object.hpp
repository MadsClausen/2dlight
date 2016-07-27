#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>

#include "math/math.hpp"
#include "shader.hpp"

namespace gfx
{
	class object_t
	{
		private:
			shader_t *_shader;
			math::vec4f _color;
			char _block_light, _solid;

		public:
			math::poly2d *shape;
			
			////////////////

			object_t();
			~object_t();

			void render();

			void set_color(math::vec4f c) { _color = c; }
	};
};

#endif