$Subshader Vertex
#version 430 core

struct MVP
{
	mat4 model;
	mat4 view;
	mat4 proj;
};

layout(location = 0) in vec3 position;

uniform MVP mvp;

out vec3 near;
out vec3 far;

vec3 Unproject(float x, float y, float z);

void main()
{
	near = Unproject(position.x, position.y, 0.0);
	far = Unproject(position.x, position.y, 1.0);

	gl_Position = vec4(position, 1.0);
}

vec3 Unproject(float x, float y, float z)
{
	mat4 viewInv = inverse(mvp.view);
	mat4 projInv = inverse(mvp.proj);

	vec4 unprojectPoint = viewInv * projInv * vec4(x, y, z, 1.0);
	return unprojectPoint.xyz / unprojectPoint.w;
}

$Subshader Fragment
#version 430 core
out vec4 fragColor;

in vec3 near;
in vec3 far;

vec4 grid(vec3 fragPos, float scale);

void main()
{
	float t = -near.y / (far.y - near.y);
    vec3 fragPos = near + t * (far - near);
    
	fragColor = grid(fragPos, 10) * float(t > 0);
}

vec4 grid(vec3 fragPos, float scale)
{
    vec2 coord = fragPos.xz * scale; // use the scale variable to set the distance between the lines
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
    // z axis
    if (fragPos.x > -0.1 * minimumx && fragPos.x < 0.1 * minimumx)
        color.z = 1.0;
    // x axis
    if (fragPos.z > -0.1 * minimumz && fragPos.z < 0.1 * minimumz)
        color.x = 1.0;
    return color;
}