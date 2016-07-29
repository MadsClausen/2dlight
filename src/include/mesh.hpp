#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"
#include "math/math.hpp"

namespace gfx
{
	class vertex_t
	{
		public:
			math::vec3f location;
			math::vec2f texcoord;

			vertex_t() {}
			vertex_t(math::vec3f v, math::vec2f t) { location = v; texcoord = t; }
	};

	class transform_t
	{
		public:
			math::vec3f translate, rotate, scale;
			math::mat4f matrix, _translate_mat, _rotate_mat, _scale_mat;

			transform_t() { translate = math::vec3f(0, 0, 0); rotate = math::vec3f(0, 0, 0); }
			~transform_t() {}

			void update_matrix();
	};


	// MESH
	class mesh_t
	{
		private:
			vertex_t *_vertices;
			unsigned int _num_vertices;
			shader_t *_shader;
			char _block_light, _solid;

			enum
			{
				POSITION_VBO,
				TEXCOORD_VBO,
				NUM_BUFFERS
			};

			GLuint _vao, _vbo[NUM_BUFFERS]; // vertexbufferobject and vertexarrayobject
			unsigned int _drawcount;

		public:
			shader_t shader;
			////////////////

			mesh_t(unsigned int nverts, vertex_t *vertices);
			~mesh_t();

			void render();

			void set_shader(shader_t *s);
	};
};

#endif