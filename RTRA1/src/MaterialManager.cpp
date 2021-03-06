#include "MaterialManager.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

MaterialManager::MaterialManager()
{
	m_ruby = Material({
		glm::vec3(0.1745f, 0.01175f, 0.01175f),
		glm::vec3(0.61424f, 0.04136f, 0.04136f),
		glm::vec3(0.727811f, 0.626959f, 0.626959f),
		0.6f * 128 });

	m_emerald = Material({
		glm::vec3(0.0215f, 0.1745f, 0.0215f),
		glm::vec3(0.07568f, 0.61424f, 0.07568f),
		glm::vec3(0.633f, 0.727811f, 0.633f),
		0.6f * 128 });

	m_turquoise = Material({
		glm::vec3(0.1f, 0.18725f, 0.1745f),
		glm::vec3(0.396f, 0.74151f, 0.69102f),
		glm::vec3(0.297254, 0.30829f, 0.306678f),
		0.1f * 128 });

	// ruby
	m_materials.push_back(Material({
		glm::vec3(0.1745f, 0.01175f, 0.01175f),
		glm::vec3(0.61424f, 0.04136f, 0.04136f),
		glm::vec3(0.727811f, 0.626959f, 0.626959f),
		0.6f * 128 }));

	// emerald
	m_materials.push_back(Material({
		glm::vec3(0.0215f, 0.1745f, 0.0215f),
		glm::vec3(0.07568f, 0.61424f, 0.07568f),
		glm::vec3(0.633f, 0.727811f, 0.633f),
		0.6f * 128 }));

	// turquoise
	m_materials.push_back(Material({
		glm::vec3(0.1f, 0.18725f, 0.1745f),
		glm::vec3(0.396f, 0.74151f, 0.69102f),
		glm::vec3(0.297254, 0.30829f, 0.306678f),
		0.1f * 128 }));

	m_activeMaterial = &m_ruby;
}

// for fixed function pipeline
void MaterialManager::setMaterial(MaterialName name, bool hasLights) {
	switch (name) {
	case MaterialName::RUBY:
		m_activeMaterial = &m_ruby;
		break;
	case MaterialName::EMERALD:
		m_activeMaterial = &m_emerald;
		break;
	case MaterialName::TURQUOISE:
		m_activeMaterial = &m_turquoise;
		break;
	}

	if (hasLights)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, (const float*)glm::value_ptr(m_activeMaterial->ambient));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, (const float*)glm::value_ptr(m_activeMaterial->diffuse));
		glMaterialfv(GL_FRONT, GL_SPECULAR, (const float*)glm::value_ptr(m_activeMaterial->specular));
		glMaterialf(GL_FRONT, GL_SHININESS, m_activeMaterial->shininess);
	} else
	{
		glm::vec3 colour = m_activeMaterial->ambient + m_activeMaterial->diffuse;
		glColor3f(colour.x, colour.y, colour.z);
	}
}

const Material MaterialManager::getMaterialByName(MaterialName name) const {
	switch (name) {
	case MaterialName::RUBY:
		return m_ruby;
	case MaterialName::EMERALD:
		return m_emerald;
	case MaterialName::TURQUOISE:
		return m_turquoise;
	}
}

const std::vector<Material> MaterialManager::getMaterials() const {
	return m_materials;
}