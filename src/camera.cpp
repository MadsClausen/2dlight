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
		_enabled = 1;
	}

	void camera_t::update()
	{
		_proj_mat = math::perspective_mat4(_fov_y, _aspect, _near, _far);
		_view_mat = math::look_to(pos, dir);

		if(_enabled)
		{
			// send matrices to shaders
			for(int i = 0; i < _shaders.size(); i++)
			{
				printf("sending matrices to shader with id %u\n", _shaders[i]->get_id());
				_shaders[i]->bind();
				glUniformMatrix4fv(_shaders[i]->get_uniform_location(UNIFORM_VIEW_MATRIX), 1, GL_FALSE, &_view_mat[0]);
				glUniformMatrix4fv(_shaders[i]->get_uniform_location(UNIFORM_PROJECTION_MATRIX), 1, GL_FALSE, &_proj_mat[0]);
				glUniform3fv(_shaders[i]->get_uniform_location(UNIFORM_CAMERA_LOCATION), 1, &pos[0]);
			}
		}
	}
}