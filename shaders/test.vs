#version 150

in vec4 location;
in vec4 normal;

out Vertex
{
  vec4 normal;
  vec4 color;
} vertex;

void main()
{
  gl_Position = location;
  
  vertex.normal = normal;
  vertex.color =  vec4(1.0, 1.0, 0.0, 1.0);
}