#include "camera.hpp"

namespace gfx
{
	camera_t::camera_t(math::vec3f p, math::vec3f d, float fov_y, float aspect, float near, float far)
	{
		pos = p;
		dir = d;
		_fov_y = fov_y;
		_aspect = aspect;
		_near = near;
		_far = far;

		_proj_mat = math::perspective_mat4(_fov_y, _aspect, _near, _far);
		_view_mat = math::look_to(pos, dir);
		out_mat = _proj_mat * _view_mat;
	}

	void camera_t::update()
	{
		_proj_mat = math::perspective_mat4(_fov_y, _aspect, _near, _far);
		_view_mat = math::look_to(pos, dir);
		out_mat = _proj_mat * _view_mat;
	}
}