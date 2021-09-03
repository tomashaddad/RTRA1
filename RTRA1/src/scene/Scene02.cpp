#include "Scene02.h"

#include "RTRApp.h"

#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Scene02::Scene02()
	: ModernScene(std::make_shared<Shader>(
		"./src/shaders/scene02/menger.vert",
		"./src/shaders/scene02/menger.frag",
		"./src/shaders/scene02/menger.geom")) {}

void Scene02::init() {
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

void Scene02::render() {
	glm::mat4 model = m_transformation.getModelMatrix(); // default
	glm::mat4 view = RTRApp::instance().getCamera()->getViewMatrix();
	glm::mat4 projection = RTRApp::instance().getCamera()->getProjectionMatrix();

	m_shader->bind();
	m_shader->setMat4("model", model);
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);
	m_shader->setVec3f("viewPos", RTRApp::instance().getCamera()->getPosition());

	m_shader->setMaterial("ruby", m_materialManager.getMaterialByName(MaterialName::RUBY));
	m_shader->setMaterial("emerald", m_materialManager.getMaterialByName(MaterialName::EMERALD));
	m_shader->setMaterial("turquoise", m_materialManager.getMaterialByName(MaterialName::TURQUOISE));

	m_shader->setInt("lighting", m_lighting);

	m_shader->setInt("lightNumber", m_lightNumber);

	setDirectionalLight("directionalLight", m_lightManager.getDirectionalLight());

	for (int i = 0; i < m_lightNumber; ++i) {
		setPointLight("pointLights", m_lightManager.getPointLights()[i], i);
	}

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_menger.indices.size(), GL_UNSIGNED_INT, 0);
}