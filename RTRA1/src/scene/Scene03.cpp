#include "Scene03.h"

#include "RTRApp.h"

#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>

Scene03::Scene03()
	: ModernScene(std::make_shared<Shader>(
		"./src/shaders/scene03/menger.vert",
		"./src/shaders/scene03/menger.frag",
		"./src/shaders/scene03/menger.geom"))
	, m_rotationSpeed(10.0f)
{
	// A sphere has radius r = sqrt(3)s/2 for a cube of side length s
	// So each square containing a rotating menger has dimensions sqrt(3)/2 * sqrt(3)/2
	float radius = sqrt(3);
	int index = 0;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			m_transformations[index].setTranslation(glm::vec3(i * radius, j * radius, 0));
			m_transformations[index].setRotation(glm::ballRand(1.0f)); // default 0 degrees
			++index;
		}
	}
}

void Scene03::init() {
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

void Scene03::render() {
	glm::mat4 model = m_transformation.getModelMatrix(); // default
	glm::mat4 view = RTRApp::instance().getCamera()->getViewMatrix();
	glm::mat4 projection = RTRApp::instance().getCamera()->getProjectionMatrix();

	m_shader->bind();
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
	
	for (auto& transformation : m_transformations) {
		transformation.rotateByDegrees(1);
		m_shader->setMat4("model", transformation.getModelMatrix());
		glDrawElements(GL_TRIANGLES, m_menger.indices.size(), GL_UNSIGNED_INT, 0);
	}
}