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
		std::vector<math::vec4f> colors;

		for(unsigned int i = 0; i < nverts; i++)
		{
			locations.push_back(vertices[i].location);
			texcoords.push_back(vertices[i].texcoord);
			colors.push_back(vertices[i].color);

			printf("color = (%f, %f, %f, %f)\n", vertices[i].color.x, vertices[i].color.y, vertices[i].color.z, vertices[i].color.w);
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

		glBindVertexArray(0);


	}

	mesh_t::~mesh_t() {}

	void mesh_t::render()
	{
		glBindVertexArray(_vao);

		_texture->bind(0);
		_shader->bind();
		glDrawArrays(GL_TRIANGLES, 0, _num_vertices);

		glBindVertexArray(0);
	}

	void mesh_t::set_shader(shader_t *s)
	{
		_shader = s;
        glBindAttribLocation(_shader->get_id(), 0, "location");
        glBindAttribLocation(_shader->get_id(), 1, "texcoord");
        glBindAttribLocation(_shader->get_id(), 2, "color");

        _shader->bind();
        _uniforms[UNIFORM_MVP] = _shader->get_uniform_location("MVP");
	}

	void mesh_t::update()
	{
		_shader->bind();
		glUniformMatrix4fv(_uniforms[UNIFORM_MVP], 1, GL_FALSE, &_transform->matrix[0]);
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