#include "ModernScene.h"

#include <iostream>

// TODO: Creates a copy of the shader so destructor is called
// once ModernScene's constructor is complete

ModernScene::ModernScene(Shader shader)
	: m_VAO(0)
	, m_VBO(0)
	, m_EBO(0)
	, m_shader(shader)
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
}

ModernScene::~ModernScene() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void ModernScene::incrementSubdivisions() {
	SceneBase::incrementSubdivisions();
	updateLayout();
}

void ModernScene::decrementSubdivisions() {
	SceneBase::decrementSubdivisions();
	updateLayout();
}

void ModernScene::updateLayout() {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_menger.vertices.size(), m_menger.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_menger.indices.size(), m_menger.indices.data(), GL_STATIC_DRAW);
}