#include "scene.hpp"

#include "gfx.hpp"

namespace gfx
{
	scene_t::scene_t()
	{
		_num_lights = 0;

		// create light data buffer
		printf("generating buffer\n");
		glGenBuffers(1, &_light_data_buffer);
		printf("generated buffer: %u\n", _light_data_buffer);

		glBindBuffer(GL_UNIFORM_BUFFER, _light_data_buffer);
		glBufferData(_light_data_buffer, sizeof(shader_light_t) * MAX_LIGHTS, &_lights[0], GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT_DATA_BINDING_POINT, _light_data_buffer);
	}

	scene_t::~scene_t()
	{

	}

	void scene_t::render()
	{
		for(int i = 0; i < _meshes.size(); i++)
		{
			_meshes[i]->render();
		}	
	}

	void scene_t::add_mesh(mesh_t *o)
	{
		_meshes.push_back(o);
	}

	void scene_t::add_light_shader(shader_t *s)
	{
		_light_shaders.push_back(s);

		// bind uniform block in new shader to proper binding point
		glUniformBlockBinding(s->get_id(), s->get_uniform_block_index(UNIFORM_BLOCK_LIGHTS), LIGHT_DATA_BINDING_POINT);
	}

	char scene_t::add_light(light_t *l)
	{

		if(_num_lights >= MAX_LIGHTS) return 0;

		_lights[_num_lights] = l;

		_num_lights++;
	}

	void scene_t::update_light_data()
	{
		for(int i = 0; i < _light_shaders.size(); i++)
		{
			_light_shaders[i]->bind();
			glUniform1i(_light_shaders[i]->get_uniform_location(UNIFORM_NUM_LIGHTS), _num_lights);
		}

		// produce array of shader lights
		shader_light_t _shader_lights[MAX_LIGHTS];
		for(int i = 0; i < _num_lights; i++)
		{
			_shader_lights[i] = _lights[i]->_shader_light_struct;
		}

		glBindBuffer(GL_UNIFORM_BUFFER, _light_data_buffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(_shader_lights), &_shader_lights[0], GL_DYNAMIC_DRAW);
	}
}