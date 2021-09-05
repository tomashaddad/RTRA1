#version 460 core

layout ( triangles ) in;
layout ( triangle_strip, max_vertices = 3) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vData {
	vec3 fragmentPosition;
	mat4 model;
} vertexOut[];

out gData {
	vec3 fragmentPosition;
} geometryOut;

out vec3 outNormal;

out int matindex;

void main() {
	vec3 vector0 = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
	vec3 vector1 = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
	vec3 surfaceNormal = vec3(normalize(cross(vector0, vector1)));

	int selected_mat;

	if (abs(surfaceNormal.x) > 0) {
		selected_mat = 0;
	} else if (abs(surfaceNormal.y) > 0) {
		selected_mat = 1;
	} else if (abs(surfaceNormal.z) > 0) {
		selected_mat = 2;
	}

	for (int i = 0; i < 3; ++i) {
		matindex = selected_mat;
		geometryOut.fragmentPosition = vertexOut[i].fragmentPosition;
		outNormal = mat3(transpose(inverse(vertexOut[i].model))) * surfaceNormal.xyz;
		gl_Position = projection * view * vertexOut[i].model * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}