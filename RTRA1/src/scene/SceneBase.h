#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>

class SceneBase {
public:
	SceneBase();
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void quit() = 0;

protected:
	virtual void recursiveMenger(float x, float y, float z, float edgeLength, int currentDivisions, int maxSubdivisions);
	virtual void generateCubeVerticesAt(float x, float y, float z, float edgeLength);

	std::vector<glm::vec3> m_vertices;
	std::vector<unsigned int> m_indices;

	const std::array<unsigned int, 36> m_baseIndices =
	  { 0, 2, 1,
		1, 2, 3,
		1, 3, 5,
		5, 3, 7,
		5, 7, 4,
		4, 7, 6,
		4, 6, 0,
		0, 6, 2,
		4, 0, 5,
		5, 0, 1,
		2, 6, 3,
		3, 6, 7 };
};