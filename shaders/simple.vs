#version 120

attribute vec3 location;
attribute vec2 texcoord;

varying vec2 texcoord_frag;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(location, 1.0);
	// gl_Position = vec4(location, 1.0);
	texcoord_frag = texcoord;
}