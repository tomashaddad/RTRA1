#pragma once

#include <glad/glad.h>

class VAO {
public:
	VAO();
	~VAO();
	void bind();
	void unbind();
	const GLuint id() const;
private:
	GLuint m_index;
};

