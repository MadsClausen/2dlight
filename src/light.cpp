#include "light.hpp"

namespace gfx
{
	light_t::light_t()
	{
		_scene_set = 0;
		type = LIGHT_TYPE_POINT;
		pos = color = dir = math::vec3f(0.0f, 0.0f, 0.0f);
	}

	light_t::~light_t()
	{}

	void light_t::update()
	{
		_shader_light_struct.pos = math::vec4f(pos, 1.0f);
		_shader_light_struct.dir = math::vec4f(dir, 1.0f);
		_shader_light_struct.color = math::vec4f(color, 1.0f);
		_shader_light_struct.angle = angle;
		_shader_light_struct.type = type;
	}
}