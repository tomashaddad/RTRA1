#include "MaterialFactory.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

MaterialFactory::MaterialFactory()
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

	m_activeMaterial = &m_ruby;
}

void MaterialFactory::setMaterial(MaterialName name) {
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

	glMaterialfv(GL_FRONT, GL_AMBIENT, (const float*)glm::value_ptr(m_activeMaterial->m_ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, (const float*)glm::value_ptr(m_activeMaterial->m_diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR, (const float*)glm::value_ptr(m_activeMaterial->m_specular));
	glMaterialf(GL_FRONT, GL_SHININESS, m_activeMaterial->shininess);
}