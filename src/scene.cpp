#include "scene.hpp"

#include "gfx.hpp"

namespace gfx
{
	scene_t::scene_t()
	{
		_out_tex = 0;
		_parent_win = 0;
	}

	scene_t::~scene_t()
	{

	}

	char scene_t::set_parent_window(game_window_t *win)
	{
		/*
		glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_parent_win = win;
		_w = win->w;
		_h = win->h;


		// generate framebuffer
		if(_fbuf == 0) glGenFramebuffers(1, &_fbuf);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbuf);

		// generate new texture
		if(_out_tex == 0) glGenTextures(1, &_out_tex);

		glBindTexture(GL_TEXTURE_2D, _out_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		// filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// configure and test
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _out_tex, 0);
		// glDrawBuffers(1, GL_COLOR_ATTACHMENT0);
		_drawbufs[0] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, _drawbufs);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			return -1;

		glActiveTexture(_out_tex);

		glPopAttrib();
		*/

		/*
		_parent_win = win;
		_w = win->w;
		_h = win->h;

		//RGBA8 2D texture, 24 bit depth texture, 256x256
	   	glGenTextures(1, &_out_tex);
	   	glBindTexture(GL_TEXTURE_2D, _out_tex);
	   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	   	//NULL means reserve texture memory, but texels are undefined
	   	//**** Tell OpenGL to reserve level 0
	   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _w, _h, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	   	//You must reserve memory for other mipmaps levels as well either by making a series of calls to
	   	//glTexImage2D or use glGenerateMipmapEXT(GL_TEXTURE_2D).
	   	//Here, we'll use :
	   	glGenerateMipmapEXT(GL_TEXTURE_2D);
	   	//-------------------------
	   	glGenFramebuffersEXT(1, &_fbuf);
	   	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbuf);
	   	//Attach 2D texture to this FBO
	   	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _out_tex, 0);
	   	//-------------------------
	   	glGenRenderbuffersEXT(1, &_depth_rb);
	   	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _depth_rb);
	   	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _w, _h);
	   	//-------------------------
	   	//Attach depth buffer to FBO
	   	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _depth_rb);
	   	//-------------------------
	   	//Does the GPU support current FBO configuration?
	   	GLenum status;
	   	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

	   	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
	   	{
	   		printf("shit\n"); return -1;
	   	}

	   	printf("tex in setup: %u\n", _out_tex);

	   */

		return 0;
	}

	void scene_t::render()
	{
		/*
		printf("fbuf: %u\n", _fbuf);
		// render to texture
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbuf);
		printf("glViewport(0, 0, %i, %i)\n", _w, _h);
		glViewport(0, 0, _w, _h);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		*/
		for(int i = 0; i < _objects.size(); i++)
		{
			_objects[i]->render();
		}
		


		return;
	}

	void scene_t::add_mesh(mesh_t *o)
	{
		_objects.push_back(o);
	}
}