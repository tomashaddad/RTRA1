#include "Scene04.h"

#include "RTRApp.h"

#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>

Scene04::Scene04()
	: ModernScene(std::make_shared<Shader>(
		"./src/shaders/scene04/menger.vert",
		"./src/shaders/scene04/menger.frag",
		"./src/shaders/scene04/menger.geom"))
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

void Scene04::render() {
	glm::mat4 model = m_transformation.getModelMatrix();
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

	m_shader->setInt("lightNumber", m_lightNumber);
	m_shader->setInt("lighting", m_lighting);
	setDirectionalLight("directionalLight", m_lightManager.getDirectionalLight());
	for (int i = 0; i < m_lightNumber; ++i) {
		setPointLight("pointLights", m_lightManager.getPointLights()[i], i);
	}

	glBindVertexArray(m_VAO);

	for (auto i = 0; i < m_transformations.size(); ++i) {
		m_transformations[i].rotateByDegrees(1);
		m_shader->setMat4("models[" + std::to_string(i) + "]", m_transformations[i].getModelMatrix());
	}
	glDrawElementsInstanced(GL_TRIANGLES, m_menger.indices.size(), GL_UNSIGNED_INT, 0, 9);
}