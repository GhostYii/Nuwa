#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normals;

layout(std140) uniform CameraMatrix
{
	mat4 proj;
	mat4 view;
};

out vec2 uv;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0);
	uv = texcoord;
	normal = mat3(transpose(inverse(model))) * normals;
	fragPos = vec3(model * vec4(position, 1.0));
}