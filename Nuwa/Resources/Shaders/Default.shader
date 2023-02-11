$Subshader Vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 uv;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);
	uv = texcoord;
}

$Subshader Fragment
#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;

uniform sampler2D tex;

void main()
{	
	fragColor = texture(tex, uv);
}