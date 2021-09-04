#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 model;

// uniform float deltaTime;
uniform float radius;

out vData {
	vec3 fragmentPosition;
} vertexOut;

void main() {

	vec3 maxVec = vec3(radius, radius, radius);

	vec3 temp = normalize(position) * radius;

	float maximum = max(max(abs(position.x), abs(position.y)), abs(position.z));

	float thisRatio = maximum / length(position);
	float maxRatio = maximum / length(maxVec);

	vec3 change = position;


	vertexOut.fragmentPosition = vec3(model * vec4(change, 1.0));
	gl_Position = vec4(change, 1.0);
}