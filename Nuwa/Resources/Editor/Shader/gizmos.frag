#version 430 core

struct Editor
{
	vec4 displayColor;
	sampler2D tex;
};

layout(location = 0) out vec4 fragColor;

in vec2 uv;

uniform Editor gizmos;

void main()
{
	fragColor = texture(gizmos.tex, uv) * gizmos.displayColor;
}