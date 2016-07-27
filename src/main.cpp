#include <stdio.h>

#include "gfx.hpp"
#include "object.hpp"

gfx::game_window_t gwin;
SDL_Event event;

int main(void)
{
	printf("2D Lighting");
	
	gfx::init();

	gwin.w = 800;
	gwin.h = 600;
	gwin.title = (char *) "2D Lighting";
	gfx::create_window(&gwin);

	gfx::set_clear_color(math::vec4f(0.0f, 0.0f, 1.0f, 1.0f));
	gfx::clear();

	math::poly2d poly;
	poly.add_vertex(math::vec2f(0.0f, 1.0f));
	poly.add_vertex(math::vec2f(-1.0f, -1.0f));
	poly.add_vertex(math::vec2f(1.0f, -1.0f));
	
	gfx::object_t o;
	o.set_color(math::vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	o.shape = &poly;

	o.render();
	gfx::flip(&gwin);

	SDL_Delay(2000);

	gfx::clear();

	poly.add_vertex(1.0f, 0.0f);
	o.render();
	gfx::flip(&gwin);

	char run = 1;
	while(run)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				run = 0;
			}
		}
	}

	gfx::destroy_window(&gwin);
	gfx::destroy();

	return 0;
}