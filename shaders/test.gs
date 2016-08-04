#version 150

layout(triangles) in;

// Three lines will be generated: 6 vertices
layout(line_strip, max_vertices=6) out;

uniform float normal_length;
uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

in Vertex
{
  vec4 normal;
  vec4 color;
} vertex[];

out vec4 vertex_color;

void main()
{
  int i;
  for(i=0; i<gl_in.length(); i++)
  {
    vec3 P = gl_in[i].gl_Position.xyz;
    vec3 N = vertex[i].normal.xyz;
    
    mat4 MVP * projection_mat * view_mat * model_mat;
    gl_Position = MVP * vec4(P, 1.0);
    vertex_color = vertex[i].color;
    EmitVertex();
    
    gl_Position = MVP * vec4(P + N * normal_length, 1.0);
    vertex_color = vertex[i].color;
    EmitVertex();
    
    EndPrimitive();
  }
}