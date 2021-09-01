#pragma once

#include <iostream>
#include <array>

class Triangle {
public:
	Triangle(std::array<int, 3> vertices, std::array<int, 3> normals, unsigned int material_id = 0)
		: m_vertices(vertices)
		, m_normals(normals)
		, m_matID(material_id) {}

	std::array<int, 3> m_vertices;
	std::array<int, 3> m_normals;
	unsigned int m_matID;

	friend std::ostream& operator<<(std::ostream& ostream, const Triangle& v);
};