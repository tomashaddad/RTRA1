#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>

struct Menger {
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};

class SceneBase {
public:
	SceneBase();
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void quit() = 0;

	virtual void incrementSubdivisions();
	virtual void decrementSubdivisions();

	const unsigned int getMaxSubdivisions() const;
	const unsigned int getVerticesSize() const;

protected:
	virtual void recursiveMenger(float x, float y, float z, float edgeLength, int currentDivisions, int maxSubdivisions);
	virtual void generateCubeVerticesAt(float x, float y, float z, float edgeLength);

	unsigned int m_maxSubvisions;
	float m_edgeLength;

	Menger m_menger;

	//std::vector<glm::vec3> m_vertices;
	//std::vector<unsigned int> m_indices;
	const std::array<unsigned int, 36> m_baseIndices;

private:
	void clear();
};