/******************************************
 * COPYRIGHT (C) 2014 MADS HAUPT CLAUSEN
 ******************************************/

/**
 * @file Contains definition of the shader_t class.
 * @author Mads Clausen
 */

#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include <GL/glew.h>

#define UNIFORM_MODEL_MATRIX_NAME       "model_mat"
#define UNIFORM_VIEW_MATRIX_NAME        "view_mat"
#define UNIFORM_PROJECTION_MATRIX_NAME  "projection_mat"
#define UNIFORM_CAMERA_LOCATION_NAME    "camera_location"

namespace gfx
{
    enum UNIFORM_LOCATION
    {
        UNIFORM_MODEL_MATRIX,
        UNIFORM_VIEW_MATRIX,
        UNIFORM_PROJECTION_MATRIX,
        UNIFORM_CAMERA_LOCATION,

        NUM_UNIFORMS
    };

    class shader_t
    {
        private:
            char *_vsPath, *_fsPath, *_gsPath, compiled;
            GLuint _id, _uniforms[NUM_UNIFORMS];

        public:
            /************************
             * Default constructor.
             ************************/
            shader_t()
            {
                _vsPath = (char*) "";
                _fsPath = (char*) "";
                _id = compiled = 0;

                for(int i = 0; i < NUM_UNIFORMS; i++)
                    _uniforms[i] = 0;

                prepare();
            }

            /****************************************************
             * Constructor.
             *
             * @param v The filepath to the vertex shader.
             * @param f The filepath to the fragment shader.
             ****************************************************/
            shader_t(const char *v, const char *f)
            {
                _vsPath = (char *) v;
                _fsPath = (char *) f;
                _id = compiled = 0;

                for(int i = 0; i < NUM_UNIFORMS; i++)
                    _uniforms[i] = 0;

                prepare();
            }

            ~shader_t()
            {
                glDeleteProgram(_id);
            }

            void prepare()
            {
                _id = glCreateProgram();
            }

            /***********************************************************
             * Compile the shader from source code located in files.
             ***********************************************************/
            char compile();


            /**********************************************************
             * Compile the shader from source code in strings.
             *
             * @param vertSourcePointer The vertex shader source.
             * @param fragSourcePointer The fragment shader source.
             **********************************************************/
            char compile(const char *vertSourcePointer, const char *fragSourcePointer);

            char add_geometry_shader(const char *geoSourcePointer);


            /************************************************
             * Returns the path to the vertex shader.
             *
             * @return The filepath to the vertex shader.
             ************************************************/
            const char *get_vertex_path()
            {
                return (const char*) _vsPath;
            }


            /************************************************
             * Returns the path to the fragment shader.
             *
             * @return The filepath to the fragment shader.
             ************************************************/
            const char *get_fragment_path()
            {
                return (const char *) _fsPath;
            }


            /******************************************
             * Returns the ID of the OpenGL shader.
             *
             * @return The ID.
             ******************************************/
            const GLuint get_id()
            {
                return (const GLuint) _id;
            }

            GLuint get_uniform_location(UNIFORM_LOCATION loc);


            /*********************
             * Uses the shader.
             *********************/
            void bind()
            {
                if(_id != 0)
                    glUseProgram(_id);
            }


            /**************************
             * "Unbinds" the shader.
             **************************/
            void unbind()
            {
                glUseProgram(0);
            }

            char is_compiled()
            {
                return compiled;
            }
    };
}

#endif // SHADER_INCLUDED
