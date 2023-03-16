#version 430 core

layout(quads, equal_spacing, cw) in;

layout(std140) uniform CameraMatrix
{
	mat4 proj;
	mat4 view;
};

uniform mat4 model;
uniform sampler2D heightMap;
uniform float yScale;
uniform float yShift;

in vec2 texcoord[];
out vec2 uv;

void main()
{
	float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec2 uv0 = texcoord[0];
    vec2 uv1 = texcoord[1];
    vec2 uv2 = texcoord[2];
    vec2 uv3 = texcoord[3];

    vec2 t0 = (uv1 - uv0) * u + uv0;
    vec2 t1 = (uv3 - uv2) * u + uv2;
    uv = (t1 - t0) * v + t0;

    float height = texture(heightMap, uv).y * yScale - yShift;

    vec4 pos0 = gl_in[0].gl_Position;
    vec4 pos1 = gl_in[1].gl_Position;
    vec4 pos2 = gl_in[2].gl_Position;
    vec4 pos3 = gl_in[3].gl_Position;

    vec4 uVec = pos1 - pos0;
    vec4 vVec = pos2 - pos0;
    vec4 norm = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0));

    vec4 p0 = (pos1 - pos0) * u + pos0;
    vec4 p1 = (pos3 - pos2) * u + pos2;
    vec4 pos = (p1 - p0) * v + p0 + norm * height;

    gl_Position = proj * view * model * pos; // Matrix transformations go here    
}