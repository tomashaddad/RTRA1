#include "SceneBase.h"

#include <iostream>
#include <cmath>

SceneBase::SceneBase() {
	recursiveMenger(0, 0, 0, 1, 0, 3);
}

void SceneBase::recursiveMenger(float x, float y, float z, float edgeLength, int currentSubdivision, int maxSubdivisions) {

	if (maxSubdivisions == 0) {
		generateCubeVerticesAt(0, 0, 0, edgeLength);
		return;
	}

	// x axis
	for (int i = -1; i < 2; ++i) {
		// y axis
		for (int j = -1; j < 2; ++j) {
			// z axis
			for (int k = -1; k < 2; ++k) {
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

void SceneBase::generateCubeVerticesAt(float x, float y, float z, float offset) {
	// top left, top right, bottom left, bottom right, front (+z) to back (-z)
	m_vertices.emplace_back(x - offset, y + offset, z + offset);
	m_vertices.emplace_back(x + offset, y + offset, z + offset);
	m_vertices.emplace_back(x - offset, y - offset, z + offset);
	m_vertices.emplace_back(x + offset, y - offset, z + offset);
	m_vertices.emplace_back(x - offset, y + offset, z - offset);
	m_vertices.emplace_back(x + offset, y + offset, z - offset);
	m_vertices.emplace_back(x - offset, y - offset, z - offset);
	m_vertices.emplace_back(x + offset, y - offset, z - offset);

	for (const unsigned int& baseIndex : m_baseIndices) {
		m_indices.emplace_back(baseIndex + 8 * (m_vertices.size() / 8 - 1));
	}
}

// 0 2 1, 1 2 3, 1 3 5, 5 3 7, 5 7 4, 4 7 6, 4 6 0, 0 6 2, 4 0 5, 5 0 1, 2 6 3, 3 6 7
// add them in order, multiply by 8 * the number of cubes already inserted into vector then add that to the number