#include "ModernScene.h"

#include <sstream>

ModernScene::ModernScene(std::shared_ptr<Shader> shader)
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

void ModernScene::setDirectionalLight(const std::string& lightName, const DirectionalLight& light) {
	m_shader->setVec3f("directionalLight.ambient", light.ambient);
	m_shader->setVec3f("directionalLight.diffuse", light.diffuse);
	m_shader->setVec3f("directionalLight.specular", light.specular);
	m_shader->setVec3f("directionalLight.direction", light.direction);
}

void ModernScene::setPointLight(const std::string& lightName, const PointLight& light, int index) {
	std::stringstream ss;

	ss << lightName << "[" << index << "].position";
	m_shader->setVec3f(ss.str(), light.position);

	ss.str(std::string());

	ss << lightName << "[" << index << "].ambient";
	m_shader->setVec3f(ss.str(), light.ambient);

	ss.str(std::string());

	ss << lightName << "[" << index << "].diffuse";
	m_shader->setVec3f(ss.str(), light.diffuse);

	ss.str(std::string());

	ss << lightName << "[" << index << "].specular";
	m_shader->setVec3f(ss.str(), light.specular);

	ss.str(std::string());

	ss << lightName << "[" << index << "].constant";
	m_shader->setFloat(ss.str(), light.constant);

	ss.str(std::string());

	ss << lightName << "[" << index << "].linear";
	m_shader->setFloat(ss.str(), light.linear);

	ss.str(std::string());

	ss << lightName << "[" << index << "].quadratic";
	m_shader->setFloat(ss.str(), light.quadratic);

	ss.str(std::string());
}