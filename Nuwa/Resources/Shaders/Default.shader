$Subshader Vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 uv;
//out vec3 fragPos;

uniform mat4 mvp;

void main()
{
	uv = texcoord;
	//fragPos = model * vec4(position, 1.0);
	gl_Position = mvp * vec4(position, 1.0);	
}

$Subshader Fragment
#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;

uniform sampler2D tex;

uniform vec3 lightPos;

uniform float ambient;
uniform float diffuse;
uniform float specular;

// normalæÿ’Û
uniform mat3 normal;

void main()
{	
	vec3 objColor = texture(tex, uv).xyz;

	vec3 lightColor = ambient * objColor;

	fragColor = lightColor;
	
}