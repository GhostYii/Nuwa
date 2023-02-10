%Subshader Vertex
#version 430 core

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0);
}

%Subshader Fragment
#version 430 core

out vec4 fragColor;

void main()
{	
	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}