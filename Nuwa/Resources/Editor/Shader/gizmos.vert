#version 430 core

struct MVP
{
	mat4 model;
	mat4 view;
	mat4 proj;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 uv;

uniform MVP mvp;

void main()
{
	gl_Position = mvp.proj * mvp.view * mvp.model * vec4(position, 1.0);	
	uv = texcoord;	
}