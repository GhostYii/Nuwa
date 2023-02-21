$Subshader Vertex
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
	uv = texcoord;
	normal = normals;
	fragPos = vec3(model * vec4(position, 1.0));
	gl_Position = camMatrix * model * vec4(position, 1.0);
}

$Subshader Fragment
#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;
in vec3 normal;
in vec3 fragPos;

//uniform int lightType;
uniform float intensity;
uniform vec3 lightPos;
uniform vec3 lightColor;
//uniform vec3 lightDir;
uniform sampler2D tex;

void main()
{
	vec3 ambient = intensity * lightColor;	

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	fragColor = vec4((ambient + diffuse), 1.0) * texture(tex, uv);
}