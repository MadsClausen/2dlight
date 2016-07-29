#include <stdio.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "gfx.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "types.hpp"
#include "texture.hpp"

using namespace gfx;

game_window_t gwin;
scene_t scene;
SDL_Event event;

int main(void)
{
	char run = 1;

	printf("2D Lighting\n");
	
	init();

	gwin.w = 512;
	gwin.h = 512;
	gwin.title = (char *) "2D Lighting";
	create_window(&gwin);

	vertex_t vertices[] = {	vertex_t(math::vec3f(-0.5f, 0.5f, 	0.0f), 	math::vec2f(0.0f, 0.0f)),
							vertex_t(math::vec3f(-0.5f, -0.5f, 	0.0f), 	math::vec2f(0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.0f), 	math::vec2f(1.0f, 0.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.0f), 	math::vec2f(1.0f, 0.0f)),
							vertex_t(math::vec3f(0.5f, 	-0.5f, 	0.0f), 	math::vec2f(1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, -0.5f, 	0.0f), 	math::vec2f(0.0f, 1.0f))};

	mesh_t mesh(6, vertices);
	
	shader_t shader("shaders/simple.vs", "shaders/simple.fs");
	shader.compile();
	mesh.set_shader(&shader);

	GLuint mvp_loc = shader.get_uniform_location("MVP");
	transform_t trans;
	trans.rotate = math::vec3f(0.0f, 0.0f, 45.0f);
	trans.translate = math::vec3f(0.0f, 0.0f, 0.0f);
	trans.scale = math::vec3f(1.0f, 1.0f, 1.0f);
	trans.update_matrix();

	texture_t texture("res/image.png");

	float rotate = 0, translate  = -1.0f, d_translate = 0.01f, scale = 1.0f, d_scale = 0.5f;

	if(scene.set_parent_window(&gwin) < 0)
	{
		printf("Error setting parent window\n");
		goto panic;
	}

	while(run)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				run = 0;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		// trans.translate = math::vec3f(translate += d_translate, 0.0f, 0.0f);
		if(translate >= 1.0f  && d_translate > 0) d_translate = -d_translate;
		if(translate <= -1.0f && d_translate < 0) d_translate = -d_translate;

		trans.rotate = math::vec3f(0.0f, 0.0f, scale += d_scale);

		trans.update_matrix();

		shader.bind();
		glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &trans.matrix[0]);
		shader.unbind();

		texture.bind(0);
		mesh.render();

		flip(&gwin);
	}

panic:
	destroy_window(&gwin);
	destroy();

	return 0;
}