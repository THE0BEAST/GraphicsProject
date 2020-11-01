#version 400

in vec3 in_position;
in vec3 in_normal;
in vec2 in_uv;

uniform mat4 MV;
uniform mat4 MVP;

out vec3 N;
out vec4 P;
out vec2 texCoord;

void main() 
{
	gl_Position = MVP * vec4(in_position, 1.0);

    N = normalize(mat3(MV) * in_normal);
    P = MV * vec4(in_position, 1.0);
	texCoord = in_uv;
}