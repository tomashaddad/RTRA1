#include "VAO.h"

#include <iostream>

VAO::VAO() {
	glGenVertexArrays(1, &m_index);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &m_index);
}

void VAO::bind() {
	glBindVertexArray(m_index);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

const GLuint VAO::id() const {
	return m_index;
}