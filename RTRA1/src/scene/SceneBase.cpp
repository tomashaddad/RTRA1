#include "SceneBase.h"


SceneBase::SceneBase() {
	recursiveMenger(1, 0, 1);
}

void SceneBase::recursiveMenger(float edgeLength, int currentSubdivision, int maxSubdivisions) {

	if (maxSubdivisions == 0) {
		generateCubeVerticesAt(0, 0, 0, edgeLength);
	}

	// x axis
	for (int i = 0; i < 3; ++i) {
		// y axis
		for (int j = 0; j < 3; ++j) {
			// z axis
			for (int k = 0; k < 3; ++k) {
				if (currentSubdivision < maxSubdivisions) {
					recursiveMenger(edgeLength / 3.0f, currentSubdivision + 1, maxSubdivisions);
				}
				else {
					int counter = 0;
					if (i == 1) ++counter;
					if (j == 1) ++counter;
					if (k == 1) ++counter;

					if (counter < 2) {
						generateCubeVerticesAt(-edgeLength + i * edgeLength, -edgeLength + j * edgeLength, -edgeLength + k * edgeLength, edgeLength / 2.0f);
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