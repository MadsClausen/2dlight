#include "mesh.hpp"

#include <stdlib.h>

namespace gfx
{
	void mesh_t::create_mesh(unsigned int nverts, vertex_t *vertices)
	{
		_vertices = vertices;
		_num_vertices = nverts;

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		std::vector<math::vec3f> locations;
		std::vector<math::vec2f> texcoords;
		std::vector<math::vec4f> colors;
		std::vector<math::vec3f> normals;

		for(unsigned int i = 0; i < nverts; i++)
		{
			locations.push_back(vertices[i].location);
			texcoords.push_back(vertices[i].texcoord);
			colors.push_back(vertices[i].color);
			normals.push_back(vertices[i].normal);
		}

		glGenBuffers(NUM_BUFFERS, _vbo);

		// throw data in vbo
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[POSITION_VBO]);
		glBufferData(GL_ARRAY_BUFFER, _num_vertices * sizeof(locations[0]), &locations[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 /* skipping */, 0 /* offset from start */);

		// glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEXCOORD_VBO]);
		glBufferData(GL_ARRAY_BUFFER, _num_vertices * sizeof(texcoords[0]), &texcoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo[COLOR_VBO]);
		glBufferData(GL_ARRAY_BUFFER, _num_vertices * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);


		glBindBuffer(GL_ARRAY_BUFFER, _vbo[NORMAL_VBO]);
		glBufferData(GL_ARRAY_BUFFER, _num_vertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	mesh_t::mesh_t(unsigned int nverts, vertex_t *vertices)
	{
		this->create_mesh(nverts, vertices);
	}

	mesh_t::~mesh_t() { free(_vertices); }

	void mesh_t::render()
	{
		glBindVertexArray(_vao);

		_texture->bind(0);
		_shader->bind();


		//printf("bound shader\n");
		glDrawArrays(GL_TRIANGLES, 0, _num_vertices);
		//printf("drew arrays\n");

		glBindVertexArray(0);
	}

	void mesh_t::set_shader(shader_t *s)
	{
		_shader = s;
        glBindAttribLocation(_shader->get_id(), 0, "location");
        glBindAttribLocation(_shader->get_id(), 1, "texcoord");
        glBindAttribLocation(_shader->get_id(), 2, "color");
        glBindAttribLocation(_shader->get_id(), 3, "normal");

        _model_matrix_loc = _shader->get_uniform_location(UNIFORM_MODEL_MATRIX);
	}

	void mesh_t::update()
	{
		_shader->bind();
		glUniformMatrix4fv(_model_matrix_loc, 1, GL_FALSE, &_transform->matrix[0]);
	}

	char mesh_t::load_obj(const char *path)
	{
		unsigned int nverts;
		util::parse_obj(path, &nverts, _vertices);
		this->create_mesh(nverts, _vertices);
	}

	////////////////////////////////////////////////
	////////////////////////////////////////////////

	transform_t::transform_t()
	{
		rotate = math::vec3f(0.0f, 0.0f, 0.0f);
		translate = math::vec3f(0.0f, 0.0f, 0.0f);
		scale = math::vec3f(1.0f, 1.0f, 1.0f);

		this->update_matrix();
	}

	void transform_t::update_matrix()
	{
		_translate_mat = math::translate_mat4(translate);
		_rotate_mat = math::rotation_mat4(rotate);
		_scale_mat = math::scale_mat4(scale);

		matrix = _translate_mat * _scale_mat * _rotate_mat;
	}
};