#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>


#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "gfx.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "types.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "math/math.hpp"

using namespace gfx;

game_window_t gwin;
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
	gfx::create_window(&gwin);

	scene_t scene;
	scene.set_parent_window(&gwin);

	printf("light type point: %i\n", gfx::LIGHT_TYPE_POINT);

	//*
	vertex_t vertices[] = {	
        vertex_t(math::vec3f(-10.0f,-1.0f,-10.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 1.0f, 0.0f)),
	    vertex_t(math::vec3f(-10.0f,-1.0f, 10.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 1.0f, 0.0f)),
	    vertex_t(math::vec3f(10.0f,-1.0f, -10.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 1.0f, 0.0f)),
	    vertex_t(math::vec3f(10.0f, -1.0f,-10.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 1.0f, 0.0f)),
	    vertex_t(math::vec3f(-10.0f,-1.0f,10.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 1.0f, 0.0f)),
	    vertex_t(math::vec3f(10.0f, -1.0f,10.0f), 	math::vec2f(0.0f, 0.0f),	math::vec4f(1.0f, 1.0f, 1.0f, 1.0f), math::vec3f(0.0f, 1.0f, 0.0f)),
	   };

	mesh_t ground(36, vertices);

	mesh_t mesh;
	mesh.load_obj("model.obj");
	scene.add_mesh(&ground);
	scene.add_mesh(&mesh);

	shader_t shader("shaders/simple.vs", "shaders/simple.fs");
	shader.compile();
	mesh.set_shader(&shader);
	ground.set_shader(&shader);
	
	scene.add_light_shader(&shader); // send light data to shader

	transform_t trans;
	mesh.set_transform(&trans);

	transform_t trans_ground;
	//ground.set_transform(&trans_ground);

	gfx::camera_t cam(math::vec3f(0.0f, 0.0f, 15.0f), math::vec3f(0.0f, 0.0f, -1.0f), 75.0f, 8.0f/6.0f, 0.5f, 30.0f);
	cam.add_shader(&shader);
	cam.update();

	texture_t texture("res/mads.png");
	mesh.set_texture(&texture);

	light_t light;
	light.pos = math::vec3f(3.0f, 3.0f, 3.0f);
	light.color = math::vec3f(1.0f, 0.3f, 0.3f);
	light.type = gfx::LIGHT_TYPE_POINT;
	light.update();

	light_t light2;
	light2.pos = math::vec3f(-3.0f, 3.0f, 3.0f);
	light2.color = math::vec3f(0.0f, 0.0f, 1.0f);
	light2.type = gfx::LIGHT_TYPE_POINT;
	light2.update();

	scene.add_light(&light);
	scene.add_light(&light2);

	scene.update_light_data();

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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(translate >= 7.0f  && d_translate > 0) d_translate = -d_translate;
		if(translate <= -7.0f && d_translate < 0) d_translate = -d_translate;

		trans.rotate = math::vec3f(0.0f, _rotate += d_scale, 0);
		trans.update_matrix();

		//scene.update_light_data();

		mesh.update();
		mesh.render();

		ground.update();
		ground.render();

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