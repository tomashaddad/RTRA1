#include "ModernScene.h"

#include <string>

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

void ModernScene::setDirectionalLight(const std::string lightName, const DirectionalLight light) {
	m_shader->setVec3f("directionalLight.ambient", light.ambient);
	m_shader->setVec3f("directionalLight.diffuse", light.diffuse);
	m_shader->setVec3f("directionalLight.specular", light.specular);
	m_shader->setVec3f("directionalLight.direction", light.direction);
}

void ModernScene::setPointLight(const std::string lightName, const PointLight light, int index) {
	m_shader->setVec3f(lightName + "[" + std::to_string(index) + "].position", light.position);
	m_shader->setVec3f(lightName + "[" + std::to_string(index) + "].ambient", light.ambient);
	m_shader->setVec3f(lightName + "[" + std::to_string(index) + "].diffuse", light.diffuse);
	m_shader->setVec3f(lightName + "[" + std::to_string(index) + "].specular", light.specular);
	m_shader->setFloat(lightName + "[" + std::to_string(index) + "].constant", light.constant);
	m_shader->setFloat(lightName + "[" + std::to_string(index) + "].linear", light.linear);
	m_shader->setFloat(lightName + "[" + std::to_string(index) + "].quadratic", light.quadratic);
}

void ModernScene::setMaterial(const std::string materialName, const Material material, int index) {
	m_shader->setVec3f(materialName + "[" + std::to_string(index) + "].ambient", material.ambient);
	m_shader->setVec3f(materialName + "[" + std::to_string(index) + "].diffuse", material.diffuse);
	m_shader->setVec3f(materialName + "[" + std::to_string(index) + "].specular", material.specular);
	m_shader->setFloat(materialName + "[" + std::to_string(index) + "].shininess", material.shininess);
}