#version 460 core

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 8
uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int lightNumber;
uniform bool lighting;

flat in int matindex;
uniform Material materials[3];
in vec3 outNormal;

in gData {
	vec3 fragmentPosition;
} geometryOut;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 result;
    if (lighting) {
        vec3 norm = normalize(outNormal); 
        vec3 viewDir = normalize(viewPos - geometryOut.fragmentPosition);
    
        result = calculateDirectionalLight(directionalLight, norm, viewDir);
        
        for (int i = 0; i < lightNumber; ++i) {
            result += calculatePointLight(pointLights[i], norm, geometryOut.fragmentPosition, viewDir);
        }
    } else {
        result = materials[matindex].ambient * materials[matindex].diffuse;
    }

    FragColor = clamp(vec4(result, 1.0), 0.0, 1.0);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - geometryOut.fragmentPosition);

    // Ambient
    vec3 ambient = materials[matindex].ambient * light.ambient;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = materials[matindex].diffuse * light.diffuse * diff;

    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), materials[matindex].shininess);
    vec3 specular = materials[matindex].specular * light.specular * spec;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    
    // Ambient
    vec3 ambient = materials[matindex].ambient * light.ambient;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = materials[matindex].diffuse * light.diffuse * diff;

    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), materials[matindex].shininess);
    vec3 specular = materials[matindex].specular * light.specular * spec;

    return ambient + diffuse + specular;
}