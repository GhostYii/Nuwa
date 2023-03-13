#version 430 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D renderTexture;

void main()
{
	FragColor = texture(renderTexture, uv);
}