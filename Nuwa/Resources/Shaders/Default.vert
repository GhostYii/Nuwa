#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normals;

out vec2 uv;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 camMatrix;
//uniform mat4 mvp;

void main()
{
	gl_Position = camMatrix * model * vec4(position, 1.0);
	uv = texcoord;
	normal = normals;
	fragPos = vec3(model * vec4(position, 1.0));	
}