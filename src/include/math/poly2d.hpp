#ifndef __POLY2D_HPP__
#define __POLY2D_HPP__

#include <vector>

#include "math/vec2.hpp"
#include "math/vec4.hpp"

namespace math
{
	class poly2d
	{
		private:
			std::vector<vec2f> _vertices;
			float _boundary_x, _boundary_y, _boundary_w, _boundary_h;

			void _calc_boundary();

		public:
			poly2d();
			poly2d(std::vector<vec2f> vertices);
			~poly2d();

			vec4f boundary()
			{
				return vec4f(_boundary_x, _boundary_y, _boundary_w, _boundary_h);
			}

			void add_vertex(vec2f vertex);
			void add_vertex(float x, float y);

			std::vector<vec2f> vertices() { return _vertices; }
	};
};

#endif