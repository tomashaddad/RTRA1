#include "Triangle.h"

std::ostream& operator<<(std::ostream& ostream, const Triangle& v) {
	ostream << "Vertices: " << v.m_vertices[0] << " " << v.m_vertices[1] << " " << v.m_vertices[2] << std::endl;
	ostream << "Normals: " << v.m_normals[0] << " " << v.m_normals[1] << " " << v.m_normals[2] << std::endl;

	return ostream;
}