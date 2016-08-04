#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>
#include <stdio.h>
#include <cstring>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "math/math.hpp"

#define MATERIAL_UBO_BINDING_POINT_INDEX 1
#define NUM_MATERIAL_FLOATS (sizeof(material_t) / sizeof(GLfloat))

namespace gfx
{
	/*******************************
	**** MUST MATCH STRUCT IN SHADER
	********************************/
	struct material_t
	{
		math::vec3f diffuse;
		math::vec3f specular;
		math::vec3f ambient;

		float specular_hardness;
	};

	class vertex_t
	{
		public:
			math::vec3f location;
			math::vec2f texcoord;
			math::vec4f color;
			math::vec3f normal;

			vertex_t() {}
			vertex_t(math::vec3f v, math::vec2f t, math::vec4f c, math::vec3f n) { location = v; texcoord = t; normal = n; color = c; }
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
				NORMAL_VBO,

				NUM_BUFFERS
			};

			GLuint _vao, _vbo[NUM_BUFFERS], _model_matrix_loc; // vertexbufferobject and vertexarrayobject
			unsigned int _drawcount;

		public:
			////////////////

			void create_mesh(unsigned int nverts, vertex_t *vertices);

			mesh_t()
			{
				_vertices = (vertex_t *) 0;
				_num_vertices = 0;
			}
			mesh_t(unsigned int nverts, vertex_t *vertices);
			~mesh_t();

			void render();

			char load_obj(const char *path);

			void set_shader(shader_t *s);
			void set_transform(transform_t *t) { _transform = t; }
			void set_texture(texture_t *t) { _texture = t; }
			void update();
	};


	namespace util
	{
		char parse_obj(const char *path, unsigned int *nverts, vertex_t *&vertices);
	}
};

#endif