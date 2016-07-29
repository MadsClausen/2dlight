/******************************************************************
 * <insert name>   :    Game Engine produced by Mads Clausen
 * www             :    http://anickyan.koding.com/ge
 *
 * Game engine using OpenGL 3.2 for hardware-accelerated
 * graphics, for the best performance.
 *
 * Copyright (c) Mads Clausen :: All Rights Reserved
 ******************************************************************/

#include "math/mat4.hpp"

#include <stdio.h>

namespace math
{
    mat4<float> translate_mat4(vec3<float> axis)
    {
        return mat4<float>( 1, 0, 0, axis.x,
                            0, 1, 0, axis.y,
                            0, 0, 1, axis.z,
                            0, 0, 0, 1);
    }

    mat4<float> scale_mat4(vec3<float> axis)
    {
        // printf("scale: (%f, %f, %f)\n", axis.x, axis.y, axis.z);

        mat4<float> _s_mat( axis.x, 0, 0, 0,
                            0, axis.y, 0, 0,
                            0, 0, axis.z, 0,
                            0, 0,      0, 1.0f);

        // print_mat4f(_s_mat);
        return _s_mat;
    }

    mat4<float> rotation_mat4(vec3<float> rotation)
    {
        float rot_x = rotation.x * DEGTORAD;
        float rot_y = rotation.y * DEGTORAD;
        float rot_z = rotation.z * DEGTORAD;

        double cosAx = cos(rot_x);
        double sinAx = sin(rot_x);
        double cosAy = cos(rot_y);
        double sinAy = sin(rot_y);
        double cosAz = cos(rot_z);
        double sinAz = sin(rot_z);

        mat4<float> rotX(1,     0,     0, 0,
                         0, cosAx,-sinAx, 0,
                         0, sinAx, cosAx, 0,
                         0,     0,     0, 1);

        mat4<float> rotY(cosAy, 0, sinAy, 0,
                         0,     1,     0, 0,
                        -sinAy, 0, cosAy, 0,
                         0,     0,     0, 1);

        mat4<float> rotZ(cosAz,-sinAz, 0, 0,
                         sinAz, cosAz, 0, 0,
                         0,     0,     1, 0,
                         0,     0,     0, 1);

        return rotX * rotY * rotZ;
    }

    mat4<float> perspective_mat4(float frustumScale, float aspect, float near, float far)
    {
        mat4<float> mat(
                        frustumScale / aspect,      0,                          0,                              0,
                        0,                          frustumScale,               0,                              0,
                        0,                          0,                         (far + near) / (near - far),     (2 * far * near) / (near - far),
                        0,                          0,                         -1,                              0
                        );

        return mat;
    }

    mat4<float> look_at(vec3<float> pos, vec3<float> look)
    {
        vec3<float> up(0.0f, 1.0f, 0.0f), right;

        vec3<float> dir(look.x - pos.x,
                        look.y - pos.y,
                        look.z - pos.z);
        dir = dir.normal();

        right = dir.cross(up);
        up = right.cross(dir).normal();

        mat4<float> view(
			right.x, right.y, right.z, 0.0f,
                       	up.x,    up.y,    up.z,	   0.0f,
                       -dir.x,  -dir.y,  -dir.z,   0.0f,
                       	 0.0f,    0.0f,    0.0f,   1.0f);
        mat4<float> aux;
        for(unsigned int i = 0; i < 4; ++i) aux[i + i * 4] = 1.0f; // fill diagonal

        aux[12] = -pos.x;
        aux[13] = -pos.y;
        aux[14] = -pos.z;

        return view * aux;
    }

    void print_mat4f(mat4f mat)
    {
        printf("[%f\t%f\t%f\t%f]\n[%f\t%f\t%f\t%f]\n[%f\t%f\t%f\t%f]\n[%f\t%f\t%f\t%f]\n", mat[0], mat[1], mat[2], mat[3], mat[4], mat[5], mat[6], mat[7], mat[8], mat[9], mat[10], mat[11], mat[12], mat[13], mat[14], mat[15]);
    }
};
