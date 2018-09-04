#version 330 core

// Structs
struct Material
{
	vec3 color;
};

struct DirLight
{
	vec3 dir; // Normalized
	vec3 color;
};

in vec3 Normal; // Not normalized

out vec4 FragColor;

uniform Material material;
uniform DirLight dirLight;
uniform vec3 ambientLight;

void main()
{
	// Diffuse Lighting
	vec3 norm = normalize(Normal);
	float diffuse = max(dot(norm, -dirLight.dir), 0.0);

	// Combine diffuse and ambient Light
	vec3 combinedLight = min(dirLight.color * diffuse + ambientLight, 1.0);
	vec3 result = material.color * combinedLight;

	FragColor = vec4(result, 1.0);
}