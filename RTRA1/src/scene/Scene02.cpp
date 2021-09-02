#include "Scene02.h"

#include "RTRApp.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Scene02::Scene02()
	: m_shader("./src/shaders/scene02/menger.vert", "./src/shaders/scene02/menger.frag", "./src/shaders/scene02/menger.geom")
	, m_VAO(0)
	, m_VBO(0)
	, m_EBO(0) {}

Scene02::~Scene02() {

}

void Scene02::init() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_menger.vertices.size(), m_menger.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_menger.indices.size(), m_menger.indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Scene02::updateLayout() {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_menger.vertices.size(), m_menger.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_menger.indices.size(), m_menger.indices.data(), GL_STATIC_DRAW);
}

void Scene02::incrementSubdivisions() {
	clear();
	recursiveMenger(0, 0, 0, m_edgeLength, 0, ++m_maxSubvisions);
	updateLayout();
}

void Scene02::decrementSubdivisions() {
	if (m_maxSubvisions <= 0) {
		return;
	}
	clear();
	recursiveMenger(0, 0, 0, m_edgeLength, 0, --m_maxSubvisions);
	updateLayout();
}

void Scene02::render() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = RTRApp::instance().getCamera()->getViewMatrix();
	glm::mat4 projection = RTRApp::instance().getCamera()->getProjectionMatrix();

	m_shader.bind();
	m_shader.setMat4("model", model);
	m_shader.setMat4("view", view);
	m_shader.setMat4("projection", projection);
	m_shader.setVec3f("viewPos", RTRApp::instance().getCamera()->getPosition());

	m_shader.setVec3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	m_shader.setVec3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	m_shader.setVec3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shader.setFloat("material.shininess", 32.0f);

	glm::vec3 lightPos(10.0f, 10.0f, 10.0f);
	m_shader.setVec3f("light.position", lightPos);
	m_shader.setVec3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	m_shader.setVec3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shader.setVec3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_menger.indices.size(), GL_UNSIGNED_INT, 0);

	//glBindVertexArray(0);
}