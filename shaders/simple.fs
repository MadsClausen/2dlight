#version 120

varying vec2 texcoord_frag;
varying vec4 frag_c;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texcoord_frag);
	gl_FragColor = frag_c;
}