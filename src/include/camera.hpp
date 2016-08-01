#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "math/math.hpp"

namespace gfx
{
	class camera_t
	{
		private:
			float _fov_y, _aspect, _near, _far;

		public:
			math::vec3f pos, dir;
			math::mat4f out_mat;
			
			math::mat4f _view_mat, _proj_mat;

			camera_t(math::vec3f p, math::vec3f d, float fov_y, float aspect, float near, float far);
			~camera_t() {};

			void update();
	};
}

#endif