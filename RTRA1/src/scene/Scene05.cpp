#include "Scene05.h"

#include "RTRApp.h"

#include <glm/glm.hpp>

Scene05::Scene05()
	: ModernScene(std::make_shared<Shader>(
		"./src/shaders/scene05/menger.vert",
		"./src/shaders/scene05/menger.frag",
		"./src/shaders/scene05/menger.geom")) {}

void Scene05::init() {
	glBindVertexArray(m_VAO);

	sendVerticesToBuffer();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_menger.indices.size(), m_menger.indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// it's better to create a float from getNonLinearTransformedTime() outside the loop
// but the effect of having it inside the loop is cool so I kept it!s
void Scene05::sendVerticesToBuffer() {
	glBindVertexArray(m_VAO);
	m_transformedVertices.clear();
	for (glm::vec3 position : m_menger.vertices) {
		float radius = glm::max(glm::max(glm::abs(position.x), glm::abs(position.y)), glm::abs(position.z));
		glm::vec3 unit = glm::normalize(position) * radius;
		glm::vec3 lerp = glm::mix(position, unit, getNonLinearTransformedTime());
		m_transformedVertices.push_back(lerp);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_transformedVertices.size(), m_transformedVertices.data(), GL_STATIC_DRAW);
}

void Scene05::updateLayout() {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_transformedVertices.size(), m_transformedVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_menger.indices.size(), m_menger.indices.data(), GL_STATIC_DRAW);
}

void Scene05::render() {
	sendVerticesToBuffer();
	glm::mat4 model = m_transformation.getModelMatrix(); // default
	glm::mat4 view = RTRApp::instance().getCamera()->getViewMatrix();
	glm::mat4 projection = RTRApp::instance().getCamera()->getProjectionMatrix();

	m_shader->bind();
	m_shader->setMat4("model", model);
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);
	m_shader->setVec3f("viewPos", RTRApp::instance().getCamera()->getPosition());

	const std::vector<Material>& materials = m_materialManager.getMaterials();
	for (int i = 0; i < materials.size(); ++i) {
		setMaterial("materials", materials[i], i);
	}

	m_shader->setInt("lighting", m_lighting);
	m_shader->setInt("lightNumber", m_lightNumber);
	setDirectionalLight("directionalLight", m_lightManager.getDirectionalLight());
	for (int i = 0; i < m_lightNumber; ++i) {
		setPointLight("pointLights", m_lightManager.getPointLights()[i], i);
	}

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_menger.indices.size(), GL_UNSIGNED_INT, 0);
}
