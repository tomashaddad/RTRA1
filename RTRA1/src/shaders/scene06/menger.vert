#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 model;

out vData {
	vec3 fragmentPosition;
} vertexOut;

uniform float multiplier;

void main() {
	vertexOut.fragmentPosition = vec3(model * vec4(position, 1.0));

	// the radius of the sphere the point needs to project to
	// is the same as the value of its maximum absolute component
	float radius = max(max(abs(position.x), abs(position.y)), abs(position.z));

	// vector in the direction of the point at the radius
	vec3 normal_position = normalize(position) * radius;

	vec3 lerp = mix(position, normal_position, multiplier);

	gl_Position = vec4(lerp, 1.0);
}