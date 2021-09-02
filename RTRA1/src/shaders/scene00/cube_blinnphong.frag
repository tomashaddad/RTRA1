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

in vec3 Normal;  
/* This in variable will be interpolated from the 3 world position vectors of the triangle to form
the FragPos vector that is the per-fragment world position. */
in vec3 FragPos; 

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

/* 

The Phong lightining model relies on the calculation:

    max(dot(viewDir, reflectDir), 0.0)

If the vector from the fragment to the viewer and the vector from the fragment to the reflected vector is
greater than 90 degrees, then the dot product becomes negative, and this will return 0.

This happens when the angle the light makes with the fragment is less than the angle that the viewer makes
with the fragment.

Instead of calculating the dot product between the viewer's vector and the reflected vector, the Blinn-Phong
model calculates the dot product between the viewer vector and the vector halfway between the fragment-to-viewer
vector and fragment-to-light vector. If the viewer is looking at the fragment exactly where the light's reflection
vector points, then the halfway vector is exactly aligned with the fragment normal.

Hence, the dot product between the halfway vector and the normal are used to measure specular intensity instead.

However, the halfway vector can only ever be between 0 and 45 degrees from the normal if the fragment reflects the
light source. So, the scalar returned from the dot product is smaller, meaning a larger specular exponent is needed.

*/

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
    // reflect expects first argument to point from light to fragment, negate 

    vec3 halfwayDir = normalize(lightDir + viewDir); // CHANGE WITH BLINN-PHONG

    // dot(viewDir, reflectDir) = 1 if we are looking at the fragment along the reflect vector
    // its value will decrease if we move away from it
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess); // CHANGE WITH BLINN-PHONG
    vec3 specular = material.specular * light.specular * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}