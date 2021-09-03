#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 models[9];

out vData {
	vec3 fragmentPosition;
	mat4 model;
} vertexOut;

void main() {
	vertexOut.fragmentPosition = vec3(models[gl_InstanceID] * vec4(position, 1.0));
	vertexOut.model = models[gl_InstanceID];
	gl_Position = vec4(position, 1.0);
}