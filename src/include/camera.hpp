#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "shader.hpp"
#include "math/math.hpp"

namespace gfx
{
	class camera_t
	{
		private:
			float _fov_y, _aspect, _near, _far;
			std::vector<shader_t *> _shaders; // which shaders to send view and projection matrix to

			char _enabled; // support for multiple cameras

		public:
			math::vec3f pos, dir;
			math::mat4f out_mat;
			
			math::mat4f _view_mat, _proj_mat;

			camera_t(math::vec3f p, math::vec3f d, float fov_y, float aspect, float near, float far);
			~camera_t() {};

			void update();
	
			void add_shader(shader_t *s)
			{
				_shaders.push_back(s);
			}

			void enable() { _enabled = 1; }
			void disable() { _enabled = 0; }
			void toggle() { _enabled = _enabled == 1 ? 0 : 1;}
	};
};

#endif