#version 150

in vec3 location;
in vec2 texcoord;
in vec4 color;
in vec3 normal;

out vec2 texcoord_frag;

out vec3 frag_c;
out vec3 frag_normal;
out vec3 frag_vert;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
	mat4 MVP = projection_mat * view_mat * model_mat;
	gl_Position = MVP * vec4(location, 1.0);

	texcoord_frag = texcoord;
	
	frag_c = color.xyz;

	frag_vert = location;

	frag_normal = normal;
	//mat3 normal_matrix = transpose(inverse(mat3(model_mat)));
	//frag_normal = normalize(normal_matrix * normal);
}