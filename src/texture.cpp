#include "texture.hpp"

texture_t::texture_t(const char *path)
{
	this->load(path);
}

texture_t::~texture_t()
{
	glDeleteTextures(1, &_id);
}

void texture_t::bind(unsigned int unit)
{
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void texture_t::load(const char *path)
{
	_w = _h = 0;

	int num_components;
	unsigned char *data = stbi_load(path, &_w, &_h, &num_components, 4);

	if(!data)
	{
		printf("shit\n");
	}

	printf("(w, h): (%u, %u)\n", _w, _h);

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}