#version 430 core

#define MAX_DIR_LIGHT_COUNT 1
#define MAX_POINT_LIGHT_COUNT 1
#define MAX_SPOT_LIGHT_COUNT 1

// phong-lighting model
struct PLM
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionLight
{
	vec3 direction;
	vec3 color;

	PLM plm;
};

struct PointLight
{
	vec3 position;
	vec3 color;

	// 衰减函数
	float kc;	// constant，常数项
	float kl;	// linear，一次项
	float kq;	// quadratic，二次项

	PLM plm;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	float kc;
	float kl;
	float kq;

	PLM plm;
};

struct Material
{
	sampler2D diffuseMap;
	sampler2D specularMap;

	float shininess;
};

// TODO
//struct Material
//{
//	vec4 abledo;
//	sampler2D abledoMap;
//	
//	float matallic;
//	float smoothness;
//	sampler2D matallicMap;
//
//	float shininess;
//	sampler2D specularMap;
//	sampler2D normalMap;
//	sampler2D emissionMap;
//};

layout(location = 0) out vec4 fragColor;

in vec2 uv;
in vec3 normal;
in vec3 fragPos;

uniform vec3 camPos;
uniform DirectionLight dLights[MAX_DIR_LIGHT_COUNT];
uniform PointLight pLights[MAX_POINT_LIGHT_COUNT];
uniform SpotLight sLights[MAX_SPOT_LIGHT_COUNT];
uniform Material material;

vec3 CreateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
vec3 CreatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CreateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(camPos - fragPos);

	vec3 phongLight = vec3(0);
	for (int i = 0; i < MAX_DIR_LIGHT_COUNT; i++)
		phongLight += CreateDirectionLight(dLights[i], norm, viewDir);
	for (int i = 0; i < MAX_POINT_LIGHT_COUNT; i++)
		 phongLight += CreatePointLight(pLights[i], norm, fragPos, viewDir);
//	for (int i = 0; i < MAX_SPOT_LIGHT_COUNT; i++)
//		phongLight += Cr
	fragColor = vec4(phongLight, 1.0);
}

vec3 CreateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir)
{
	vec3 dir = normalize(light.direction);	
	float diffuseAmount = max(dot(dir, normal), 0.0);
	vec3 reflectDir = reflect(dir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = light.plm.ambient * vec3(texture(material.diffuseMap, uv));
	vec3 diffuse = light.plm.diffuse * diffuseAmount * vec3(texture(material.diffuseMap, uv));
	vec3 specular = light.plm.specular * specularAmount * vec3(texture(material.specularMap, uv));

	return (ambient + diffuse + specular) * light.color;
}

vec3 CreatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 dir = normalize(light.position - fragPos);
	float diffuseAmount = max(dot(dir, normal), 0.0);
	vec3 reflectDir = reflect(dir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dis = length(light.position - fragPos);
	float attenuation = 1.0 / (light.kc + light.kl * dis + light.kq * pow(dis, 2));

	vec3 ambient = light.plm.ambient * vec3(texture(material.diffuseMap, uv));
	vec3 diffuse = light.plm.diffuse * diffuseAmount * vec3(texture(material.diffuseMap, uv));
	vec3 specular = light.plm.specular * specularAmount * vec3(texture(material.specularMap, uv));

	return (ambient + diffuse + specular) * attenuation * light.color;
}

