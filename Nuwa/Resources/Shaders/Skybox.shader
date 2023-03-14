$Subshader Vertex
#version 430 core

layout(location = 0) in vec3 position;

out vec3 uv;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec4 pos = projection * view * vec4(position, 1.0);
	gl_Position = pos.xyww;
	uv = position;
}

$Subshader Fragment
#version 430 core

out vec4 FragColor;

in vec3 uv;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, uv);
}
