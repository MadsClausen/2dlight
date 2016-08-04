#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>


#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "gfx.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "types.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "math/math.hpp"

using namespace gfx;

game_window_t gwin;
scene_t scene;
SDL_Event event;

void print_glm_mat(glm::mat4);
	
int main(void)
{
	char run = 1;

	srand(time(NULL));

	printf("3D Lighting\n");
	
	init();

	gwin.w = 800;
	gwin.h = 600;
	gwin.title = (char *) "3D Lighting";
	create_window(&gwin);

	/*
	vertex_t vertices[] = {	
        vertex_t(math::vec3f(-1.0f,-1.0f,-1.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f, 1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f,-1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f,-1.0f), 	math::vec2f(1.0f, 1.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f, 1.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(0.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(0.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f,-1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(0.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f,-1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(0.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f,-1.0f), 	math::vec2f(1.0f, 1.0f),	math::vec4f(0.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(0.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f,-1.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f, 1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(1.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f,-1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(1.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(1.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f, 1.0f), 	math::vec2f(1.0f, 1.0f),	math::vec4f(1.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(1.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f, 1.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f,-1.0f, 1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(1.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f,-1.0f), 	math::vec2f(1.0f, 1.0f),	math::vec4f(1.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(1.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f,-1.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(0.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f, 1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(0.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(0.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(0.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f,-1.0f), 	math::vec2f(1.0f, 1.0f),	math::vec4f(0.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(0.0f, 1.0f, 0.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f, 1.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(0.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f,-1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(0.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(0.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f, 1.0f, 1.0f), 	math::vec2f(1.0f, 0.0f),	math::vec4f(0.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(-1.0f, 1.0f, 1.0f), 	math::vec2f(1.0f, 1.0f),	math::vec4f(0.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f)),
	    vertex_t(math::vec3f(1.0f,-1.0f, 1.0f), 	math::vec2f(0.0f, 1.0f),	math::vec4f(0.0f, 0.0f, 1.0f, 1.0f), math::vec3f(0.0f, 0.0f, 0.0f))};

	mesh_t mesh(36, vertices);
	/*/

	mesh_t mesh;
	mesh.load_obj("model.obj");

	/*
	vertex_t vertices[] = {	vertex_t(math::vec3f(-0.5f, 0.5f, 	0.5f), 	math::vec2f(0.0f, 0.0f), math::vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, -0.5f, 	0.5f), 	math::vec2f(0.0f, 1.0f), math::vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f,	-0.5f, 	0.5f), 	math::vec2f(0.0f, 1.0f), math::vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, -0.5f, 	0.5f), 	math::vec2f(1.0f, 1.0f), math::vec4f(1.0f, 0.0f, 0.0f, 1.0f)),

							vertex_t(math::vec3f(-0.5f, 0.5f, 	-0.5f), math::vec2f(0.0f, 0.0f), math::vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, -0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	-0.5f), math::vec2f(1.0f, 0.0f), math::vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	-0.5f), math::vec2f(1.0f, 0.0f), math::vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f,	-0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, -0.5f, 	-0.5f), math::vec2f(1.0f, 1.0f), math::vec4f(0.0f, 1.0f, 0.0f, 1.0f)),

							vertex_t(math::vec3f(-0.5f, 0.5f, 	0.5f), 	math::vec2f(0.0f, 0.0f), math::vec4f(0.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, 0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(0.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(0.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(0.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f,	0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(0.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	-0.5f), math::vec2f(1.0f, 1.0f), math::vec4f(0.0f, 0.0f, 1.0f, 1.0f)),

							vertex_t(math::vec3f(-0.5f, -0.5f, 	0.5f), 	math::vec2f(0.0f, 0.0f), math::vec4f(1.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, -0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(1.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	-0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(1.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	-0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(1.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f,	-0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(1.0f, 0.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	-0.5f, 	-0.5f), math::vec2f(1.0f, 1.0f), math::vec4f(1.0f, 0.0f, 1.0f, 1.0f)),

							vertex_t(math::vec3f(0.5f, -0.5f, 	0.5f), 	math::vec2f(0.0f, 0.0f), math::vec4f(1.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, -0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(1.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(1.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(1.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f,	-0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(1.0f, 1.0f, 0.0f, 1.0f)),
							vertex_t(math::vec3f(0.5f, 	0.5f, 	-0.5f), math::vec2f(1.0f, 1.0f), math::vec4f(1.0f, 1.0f, 0.0f, 1.0f)),

							vertex_t(math::vec3f(-0.5f, -0.5f, 	0.5f), 	math::vec2f(0.0f, 0.0f), math::vec4f(0.0f, 1.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, -0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(0.0f, 1.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, 0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(0.0f, 1.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, 0.5f, 	0.5f), 	math::vec2f(1.0f, 0.0f), math::vec4f(0.0f, 1.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f,	-0.5f, 	-0.5f), math::vec2f(0.0f, 1.0f), math::vec4f(0.0f, 1.0f, 1.0f, 1.0f)),
							vertex_t(math::vec3f(-0.5f, 0.5f, 	-0.5f), math::vec2f(1.0f, 1.0f), math::vec4f(0.0f, 1.0f, 1.0f, 1.0f)),
						};
	
	mesh_t mesh(6*6, vertices);
	/*/

	shader_t shader("shaders/simple.vs", "shaders/simple.fs");
	shader.compile();
	mesh.set_shader(&shader);

	transform_t trans;
	mesh.set_transform(&trans);

	gfx::camera_t cam(math::vec3f(0.0f, 0.0f, 15.0f), math::vec3f(0.0f, 0.0f, -1.0f), 75.0f, 8.0f/6.0f, 0.5f, 30.0f);
	cam.add_shader(&shader);
	cam.update();

	texture_t texture("res/mads.png");
	mesh.set_texture(&texture);

	float _rotate = 0, translate  = -1.0f, d_translate = 0.05f, scale = 0.5f, d_scale = 0.5f;

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

		//printf("in loop\n");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(translate >= 7.0f  && d_translate > 0) d_translate = -d_translate;
		if(translate <= -7.0f && d_translate < 0) d_translate = -d_translate;

		trans.rotate = math::vec3f(0.0f, _rotate += d_scale, 0);
		trans.update_matrix();
		//printf("updated matrix\n");

		mesh.update();
		//printf("updated mesh\n");

		mesh.render();
		//printf("rendered mesh\n");

		flip(&gwin);
	}

panic:
	destroy_window(&gwin);
	destroy();

	return 0;
}

void print_glm_mat(glm::mat4 mat)
{
	printf("[%f\t%f\t%f\t%f]\n[%f\t%f\t%f\t%f]\n[%f\t%f\t%f\t%f]\n[%f\t%f\t%f\t%f]\n", 
            mat[0][0], mat[0][1], mat[0][2],  mat[0][3], 
            mat[1][0], mat[1][1], mat[1][2],  mat[1][3], 
            mat[2][0], mat[2][1], mat[2][2],  mat[2][3], 
            mat[3][0], mat[3][1], mat[3][2],  mat[3][3]);
}