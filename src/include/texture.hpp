#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <GL/glew.h>

#include "_stb_image.h"

class texture_t
{
	private:
		GLuint _id;
		int _w, _h;

	public:
		texture_t() {};
		texture_t(const char *path);
		~texture_t();

		void bind(unsigned int unit);
		void load(const char *path);
};

#endif