#pragma once

#include <glm/glm.hpp>

// Yes it's not TECHNICALLY the "factory" pattern but it's close enough!

enum class MaterialName {
	RUBY,
	EMERALD,
	TURQUOISE
};

struct Material {
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float shininess;
};

class MaterialFactory {
public:
	MaterialFactory();

	void setMaterial(MaterialName name);
	const Material getMaterialByName(MaterialName name) const;

private:
	Material* m_activeMaterial;

	Material m_ruby;
	Material m_emerald;
	Material m_turquoise;
};