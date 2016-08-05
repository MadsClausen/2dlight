#version 330 core

#define MAX_LIGHTS 20

struct light_t
{
	vec4 pos, color, dir; //for spotlight and plane
	float angle; // for spotlight
	int type; // point, spot, plane?
	float _align, _align2; // aling packing with vec4s
};

in vec2 texcoord_frag;
in vec3 frag_normal;
in vec3 frag_vert;
in vec3 frag_c;

uniform sampler2D diffuse;
uniform mat4 model_mat;
uniform mat4 view_mat;
uniform vec3 camera_location;

uniform int num_lights;
layout(shared) uniform light_block
{
	light_t lights[MAX_LIGHTS];
};

out vec4 out_color;

void main()
{
	float a = -0.5;

	// vector from surface to light in world coordinates
	vec3 frag_pos = vec3(model_mat * vec4(frag_vert, 1));
	// compensate for rotation
	mat3 normal_matrix = transpose(inverse(mat3(model_mat)));
	vec3 transformed_normal = normalize(normal_matrix * frag_normal);

	vec3 lights_result = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < num_lights; i++)
	{
		vec3 lpos = lights[i].pos.xyz;
		vec3 lcolor = lights[i].color.xyz;

		vec3 stl = lpos - frag_pos;
		float stl_dist = length(stl);

		/////////////////////////////////////////////////
		// AMBIENT
		float ambient_intensity = 0.1;
		vec3 ambient = lcolor * ambient_intensity;

		// DIFFUSE
		float diffuse_brightness = max(dot(transformed_normal, normalize(stl)), 0);
		vec3 diffuse = lcolor * diffuse_brightness * (pow(stl_dist, a));

		// SPECULAR
		float spec_intensity = 1.0;
		vec3 view_dir = normalize(camera_location - frag_pos);
		vec3 reflect_dir = reflect(-normalize(stl), transformed_normal);

		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
		vec3 specular = spec_intensity * spec * vec3(1.0, 1.0, 1.0);

		lights_result += ambient + diffuse + specular;
	}


	vec3 light_combination = lights_result * frag_c;

	out_color = vec4(light_combination, 1);
}