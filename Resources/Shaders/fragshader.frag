#version 400

in vec4 P;
in vec3 N;
in vec2 texCoord;

uniform mat4 viewMatrix;

struct Light
{
	vec4 position;
	vec3 intensity;
	vec3 ambientIntensity;
};
 
uniform Light light;

struct Material
{
	sampler2D texture;
	vec3 ambientReflection;
	vec3 diffuseReflection; 
	vec3 specularReflection;
	float shininess;
};

uniform Material material;

void main() 
{
	vec4 lightPosition = viewMatrix * light.position;
	vec3 L = normalize(vec3(lightPosition - P));
	vec3 V = normalize(vec3(vec4(0.0, 0.0, 0.0, 1.0) - P));
	vec3 H = normalize(L + V); 

	float LDotN  = dot(L, N); 
	float HDotN  = max(dot(H, N), 0.0);

	vec3 color = texture(material.texture, texCoord).rgb;
	vec3 ambient = light.ambientIntensity * material.ambientReflection;
	vec3 diffuse = light.intensity * color * LDotN;
	vec3 specular = vec3(0.0, 0.0, 0.0);

	if (LDotN > 0.0) 
	{
		if (HDotN == 0.0) HDotN = 1.0;

		specular = light.intensity * material.specularReflection * pow(HDotN, material.shininess); 
	}

	gl_FragColor = vec4(ambient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0);
}