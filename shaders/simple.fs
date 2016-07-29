#version 120

varying vec2 texcoord_frag;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texcoord_frag);
	// gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}