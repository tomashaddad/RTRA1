#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 model;

out vData {
	vec3 fragmentPosition;
} vertexOut;

void main() {
	vertexOut.fragmentPosition = vec3(model * vec4(position, 1.0));
	gl_Position = vec4(position, 1.0);
}