#include "SceneBase.h"

#include <iostream>
#include <cmath>

#include <glm/gtx/normal.hpp>

SceneBase::SceneBase()
	: m_maxSubvisions(1)
	, m_edgeLength(1)
	, m_baseIndices({
		0, 2, 1, 1, 2, 3,	// +z
		1, 3, 5, 5, 3, 7,	// +x
		5, 7, 4, 4, 7, 6,	// -z
		4, 6, 0, 0, 6, 2,	// -x
		4, 0, 5, 5, 0, 1,	// +y
		2, 6, 3, 3, 6, 7	// -y
	})	
{
	recursiveMenger(0, 0, 0, m_edgeLength, 0, m_maxSubvisions);
}

void SceneBase::incrementSubdivisions() {
	clear();
	recursiveMenger(0, 0, 0, m_edgeLength, 0, ++m_maxSubvisions);
}

void SceneBase::decrementSubdivisions() {
	if (m_maxSubvisions <= 0) {
		return;
	}
	std::cout << "Decrementing!" << std::endl;
	clear();
	recursiveMenger(0, 0, 0, m_edgeLength, 0, --m_maxSubvisions);
}

void SceneBase::recursiveMenger(float x, float y, float z, float edgeLength, int currentSubdivision, int maxSubdivisions) {

	if (maxSubdivisions == 0) {
		generateCubeVerticesAt(0, 0, 0, edgeLength / 2.0f);
		return;
	}

	for (int i = -1; i < 2; ++i) { // x
		for (int j = -1; j < 2; ++j) { // y
			for (int k = -1; k < 2; ++k) { // z
				int sum = abs(i) + abs(j) + abs(k);
				if (sum > 1) {
					float thirdEdge = edgeLength / 3.0f;
					float newX = x + i * thirdEdge;
					float newY = y + j * thirdEdge;
					float newZ = z + k * thirdEdge;
					if (currentSubdivision < maxSubdivisions - 1) {
						recursiveMenger(newX, newY, newZ, thirdEdge, currentSubdivision + 1, maxSubdivisions);
					} else if (currentSubdivision == maxSubdivisions - 1) {
						generateCubeVerticesAt(newX, newY, newZ, thirdEdge / 2.0f);
					}
				}
			}
		}
	}
}

// Cube vertices are drawn relative to the center of the cube. So, to go from the center
// to one of the corners, half the edge length is needed (here named offset)
void SceneBase::generateCubeVerticesAt(float x, float y, float z, float offset) {
	// top left, top right, bottom left, bottom right, front (+z) to back (-z)
	m_menger.vertices.emplace_back(x - offset, y + offset, z + offset);
	m_menger.vertices.emplace_back(x + offset, y + offset, z + offset);
	m_menger.vertices.emplace_back(x - offset, y - offset, z + offset);
	m_menger.vertices.emplace_back(x + offset, y - offset, z + offset);
	m_menger.vertices.emplace_back(x - offset, y + offset, z - offset);
	m_menger.vertices.emplace_back(x + offset, y + offset, z - offset);
	m_menger.vertices.emplace_back(x - offset, y - offset, z - offset);
	m_menger.vertices.emplace_back(x + offset, y - offset, z - offset);

	for (const unsigned int& baseIndex : m_baseIndices) {
		m_menger.indices.emplace_back(baseIndex + 8 * (m_menger.vertices.size() / 8 - 1));
	}

	//unsigned int multiplier = 8 * (m_vertices.size() / 8 - 1);
	//for (auto i = 0; i < m_baseIndices.size() - 3; i += 3) {
	//	glm::vec3 p1 = m_vertices[m_baseIndices[i] + multiplier];
	//	glm::vec3 p2 = m_vertices[m_baseIndices[i+1] + multiplier];
	//	glm::vec3 p3 = m_vertices[m_baseIndices[i+2] + multiplier];

	//	glm::vec3 normal = glm::normalize(glm::triangleNormal(p1, p2, p3));

	//	m_triangles.push_back(Triangle(
	//		{m_baseIndices[i] + multiplier, m_baseIndices[i + 1] + multiplier, m_baseIndices[i + 2] + multiplier },
	//		{normal.x, normal.y, normal.z}
	//	));
	//}
}

// 0 2 1, 1 2 3, 1 3 5, 5 3 7, 5 7 4, 4 7 6, 4 6 0, 0 6 2, 4 0 5, 5 0 1, 2 6 3, 3 6 7
// add them in order, multiply by 8 * the number of cubes already inserted into vector then add that to the number

void SceneBase::clear() {
	m_menger.vertices.clear();
	m_menger.indices.clear();
}