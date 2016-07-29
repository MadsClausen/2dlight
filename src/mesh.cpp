#include "mesh.hpp"

namespace gfx
{
	mesh_t::mesh_t(unsigned int nverts, vertex_t *vertices)
	{
		_vertices = vertices;
		_num_vertices = nverts;

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		std::vector<math::vec3f> locations;
		std::vector<math::vec2f> texcoords;

		for(unsigned int i = 0; i < nverts; i++)
		{
			locations.push_back(vertices[i].location);
			texcoords.push_back(vertices[i].texcoord);
		}


		glGenBuffers(NUM_BUFFERS, _vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[POSITION_VBO]);

		// throw data in vbo
		glBufferData(GL_ARRAY_BUFFER, _num_vertices * sizeof(locations[0]), &locations[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 /* skipping */, 0 /* offset from start */);

		// glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEXCOORD_VBO]);
		glBufferData(GL_ARRAY_BUFFER, _num_vertices * sizeof(texcoords[0]), &texcoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);


	}

	mesh_t::~mesh_t() {}

	void mesh_t::render()
	{
		glBindVertexArray(_vao);

		_shader->bind();
		glDrawArrays(GL_TRIANGLES, 0, _num_vertices);
		_shader->unbind();

		glBindVertexArray(0);
	}

	void mesh_t::set_shader(shader_t *s)
	{
		_shader = s;
        glBindAttribLocation(_shader->get_id(), 0, "location");
        glBindAttribLocation(_shader->get_id(), 1, "texcoord");
	}

	////////////////////////////////////////////////
	////////////////////////////////////////////////

	void transform_t::update_matrix()
	{
		_translate_mat = math::translate_mat4(translate);
		_rotate_mat = math::rotation_mat4(rotate);
		_scale_mat = math::scale_mat4(scale);

		matrix = _scale_mat * _translate_mat * _rotate_mat;
	}
};