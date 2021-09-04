#include "LightManager.h"

#include "RTRApp.h"

LightManager::LightManager() {
	// m_directional is updated per frame

	float d = 5.0f;
	float i = 0.8;

	// white
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(i, i, i),
		glm::vec3(i, i, i), glm::vec3(d, d, d), 1.0f, 0.045, 0.0075);

	// red
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(i, 0.0, 0.0),
		glm::vec3(i, 0.0, 0.0), glm::vec3(d, d, -d), 1.0f, 0.045, 0.0075);

	// yellow
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(i, i, 0.0),
		glm::vec3(i, i, 0.0), glm::vec3(d, -d, d), 1.0f, 0.045, 0.0075);

	// pink
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(i, 0.0, i),
		glm::vec3(i, 0.0, i), glm::vec3(d, -d, -d), 1.0f, 0.045, 0.0075);

	// green
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, i, 0.0),
		glm::vec3(0.0, i, 0.0), glm::vec3(-d, d, d), 1.0f, 0.045, 0.0075);

	// purple
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5 * i, 0.0, i),
		glm::vec3(0.5 * i, 0.0, i), glm::vec3(-d, d, -d), 1.0f, 0.045, 0.0075);

	// orange
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(i, 0.5 * i, 0.0),
		glm::vec3(i, 0.5 * i, 0.0), glm::vec3(-d, -d, d), 1.0f, 0.045, 0.0075);

	// blue
	addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, i),
		glm::vec3(0.0, 0.0, i), glm::vec3(-d, -d, -d), 1.0f, 0.045, 0.0075);
}

// Requires C++17 for struct-in-struct initialiser lists

void LightManager::addPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
	glm::vec3 position, float constant, float linear, float quadratic) {
	m_pointLights.push_back(PointLight(
		{ { LightType::POINT, ambient, diffuse, specular }, position, constant, linear, quadratic }
	));
}

const DirectionalLight& LightManager::getDirectionalLight() const {
	return DirectionalLight(
		{ {LightType::DIRECTIONAL, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f)}, RTRApp::instance().getCamera()->getForwardVector()}
	);
}

const std::vector<PointLight>& LightManager::getPointLights() const {
	return m_pointLights;
}