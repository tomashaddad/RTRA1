#version 460 core

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 outNormal;

in gData {
	vec3 fragmentPosition;
} geometryOut;

void main() {
    // Ambient
    vec3 ambient = material.ambient * light.ambient;

    // Diffuse
    vec3 norm = normalize(outNormal); 
    vec3 lightDir = normalize(light.position - geometryOut.fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * light.diffuse * diff;

    // Specular
    vec3 viewDir = normalize(viewPos - geometryOut.fragmentPosition); 
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = material.specular * light.specular * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}