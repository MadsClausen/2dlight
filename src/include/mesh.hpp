#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "math/math.hpp"

namespace gfx
{
	class vertex_t
	{
		public:
			math::vec3f location;
			math::vec2f texcoord;
			math::vec4f color;

			vertex_t() {}
			vertex_t(math::vec3f v, math::vec2f t, math::vec4f c) { location = v; texcoord = t; color = c; }
	};

	class transform_t
	{
		public:
			math::vec3f translate, rotate, scale;
			math::mat4f matrix, _translate_mat, _rotate_mat, _scale_mat;

			transform_t();
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
			transform_t *_transform;
			texture_t *_texture;

			char _block_light, _solid;

			enum
			{
				POSITION_VBO,
				TEXCOORD_VBO,
				COLOR_VBO,
				NUM_BUFFERS
			};

			enum
			{
				UNIFORM_MVP,
				NUM_UNIFORMS
			};

			GLuint _vao, _vbo[NUM_BUFFERS], _uniforms[NUM_UNIFORMS]; // vertexbufferobject and vertexarrayobject
			unsigned int _drawcount;

		public:
			////////////////

			mesh_t(unsigned int nverts, vertex_t *vertices);
			~mesh_t();

			void render();

			void set_shader(shader_t *s);
			void set_transform(transform_t *t) { _transform = t; }
			void set_texture(texture_t *t) { _texture = t; }
			void update();
	};
};

#endif