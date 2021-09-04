#pragma once

#include <glm/glm.hpp>
#include <vector>

enum class MaterialName {
	RUBY,
	EMERALD,
	TURQUOISE
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class MaterialManager {
public:
	MaterialManager();

	void setMaterial(MaterialName name);
	const Material getMaterialByName(MaterialName name) const;
	const std::vector<Material> getMaterials() const;

private:
	Material* m_activeMaterial;

	std::vector<Material> m_materials;

	Material m_ruby;
	Material m_emerald;
	Material m_turquoise;
};