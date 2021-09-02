#version 330 core
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

in vec3 Normal;  
/* This in variable will be interpolated from the 3 world position vectors of the triangle to form
the FragPos vector that is the per-fragment world position. */
in vec3 FragPos; 

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // AMBIENT
    vec3 ambient = material.ambient * light.ambient;

    // DIFFUSE
    // fragment reflects more of the light's colour if it is oriented in the direction of the light
    vec3 norm = normalize(Normal); 
    vec3 lightDir = normalize(light.position - FragPos); // from fragment to light
    float diff = max(dot(norm, lightDir), 0.0); // get a scalar between 0 and 1 (between -1 and 0 means fragment faces away from light, so make the minimum 0)
    vec3 diffuse = material.diffuse * light.diffuse * diff;

    // SPECULAR
    vec3 viewDir = normalize(viewPos - FragPos); // from fragment to viewing position
    // reflect returns a vector from the fragment to the reflection of the light direction around the fragment norm
    // reflect expects first argument to point from light to fragment, negate it
    vec3 reflectDir = reflect(-lightDir, norm);
    // dot(viewDir, reflectDir) = 1 if we are looking at the fragment along the reflect vector
    // its value will decrease if we move away from it
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * light.specular * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}