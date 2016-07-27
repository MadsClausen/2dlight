#include "math/poly2d.hpp"

namespace math
{
	poly2d::poly2d()
	{
		_boundary_x = _boundary_y = _boundary_w = _boundary_h = 0.0f;
	}

	poly2d::poly2d(std::vector<vec2f> vertices)
	{
		_vertices = vertices;
		_calc_boundary();
	}

	poly2d::~poly2d() {}

	void poly2d::_calc_boundary()
	{
		float lo_x = 0, lo_y = 0;
		float hi_x = 0, hi_y = 0;
		for(int i = 0; i < _vertices.size(); ++i)
		{
			if(i == 0) { lo_x = _vertices[i].x; lo_y = _vertices[i].y; }

			if(_vertices[i].x < lo_x) lo_x = _vertices[i].x;
			if(_vertices[i].x > hi_x) hi_x = _vertices[i].x;

			if(_vertices[i].y < lo_y) lo_y = _vertices[i].y;
			if(_vertices[i].y > hi_y) hi_y = _vertices[i].y;
		}

		_boundary_x = lo_x; 
		_boundary_y = lo_y; 
		_boundary_w = hi_x - lo_x; 
		_boundary_h = hi_y - lo_y;
	}

	void poly2d::add_vertex(vec2f v)
	{
		_vertices.push_back(v);
		_calc_boundary();
	}

	void poly2d::add_vertex(float x, float y)
	{
		_vertices.push_back(math::vec2f(x, y));
		_calc_boundary();
	}
}