$Subshader Vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normals;

out vec2 uv;
out vec3 normal;

uniform mat4 mvp;

void main()
{
	uv = texcoord;
	gl_Position = mvp * vec4(position, 1.0);	
}

$Subshader Fragment
#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;
in vec3 normal;

uniform sampler2D tex;

void main()
{	
	fragColor = texture(tex, uv);	
}