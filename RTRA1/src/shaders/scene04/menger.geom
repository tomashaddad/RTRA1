#version 460 core

// Allowed in: points, lines, lines_adjacency, triangles, triangles_adjacency
// Allowed out: points, line_strip, triangle_strip
layout ( triangles ) in;
layout ( triangle_strip, max_vertices = 3) out;

/*

If you wanted input from the vertex shader
they must come as an array, i.e.

in DATA {
	vec3 Normal;
	vec3 color;
	// etc
} data_in[];

So in the vertex shader you would have the
same thing but out DATA {...}

The current position does not need to be passed in
because the geometry shader has a default structure:

in gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
} gl_in[];

*/

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform mat4 view;
uniform mat4 projection;

uniform Material ruby;
uniform Material emerald;
uniform Material turquoise;

in vData {
	vec3 fragmentPosition;
	mat4 model;
} vertexOut[];

out gData {
	vec3 fragmentPosition;
} geometryOut;

out vec3 outNormal;
out Material material;

void main() {
	vec3 vector0 = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
	vec3 vector1 = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
	vec4 surfaceNormal = vec4(normalize(cross(vector0, vector1)), 0.0);

	Material temp;

	if (abs(surfaceNormal.x) == 1) {
		temp = ruby;
	} else if (abs(surfaceNormal.y) == 1) {
		temp = emerald;
	} else if (abs(surfaceNormal.z) == 1) {
	temp = turquoise;
	}

	for (int i = 0; i < 3; ++i) {
		material = temp;
		geometryOut.fragmentPosition = vertexOut[i].fragmentPosition;
		outNormal = mat3(transpose(inverse(vertexOut[i].model))) * surfaceNormal.xyz;
		gl_Position = projection * view * vertexOut[i].model * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}