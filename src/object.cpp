#include "object.hpp"

namespace gfx
{
	object_t::object_t()
	{
		_color = math::vec4f(0.0f, 0.0f, 0.0f, 0.0f);
		_block_light = _solid = 1;
	}

	object_t::~object_t() {}

	void object_t::render()
	{
		glColor4f(_color.x, _color.y, _color.z, _color.w);

		std::vector<math::vec2f> verts = shape->vertices();

		glBegin(GL_TRIANGLE_STRIP);
		{
			for(int i = 0; i < verts.size(); i++)
			{
				glVertex2f(verts[i].x, verts[i].y);
			}
		}
		glEnd();
	}
};