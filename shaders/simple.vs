#version 120

attribute vec3 location;
attribute vec2 texcoord;
attribute vec4 color;

varying vec2 texcoord_frag;
varying vec4 frag_c;

uniform mat4 MVP;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 rot;

void main()
{
	//vec4 loc = MVP * vec4(location, 1.0);
	//loc.w = 1.0;
	//gl_Position = proj * view * MVP * rot * vec4(location, 1.0);
	gl_Position = MVP * vec4(location, 1.0);
	texcoord_frag = texcoord;
	frag_c = color;
}