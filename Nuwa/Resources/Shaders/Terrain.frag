#version 430 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D mainTex;

void main()
{
	FragColor = texture(mainTex, uv);
}