#pragma once

#include "Transformation.h"
#include "SceneBase.h"
#include "api/Shader.h"

#include <memory>

class ModernScene : public SceneBase {
public:
	// Constructor takes a shared pointer to prevent copying of
	// internal shader object (effectively acts as a program counter)
	ModernScene(std::shared_ptr<Shader> shader);
	virtual ~ModernScene() override;
	virtual void init() override;
	virtual void render() = 0;
	virtual void incrementSubdivisions() override;
	virtual void decrementSubdivisions() override;

protected:
	virtual void updateLayout();
	void setDirectionalLight(const std::string lightName, const DirectionalLight light);
	void setPointLight(const std::string lightName, const PointLight light, int index);
	void setMaterial(const std::string materialName, const Material material, int index);
	const float getNonLinearTransformedTime() const;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	std::shared_ptr<Shader> m_shader;
	Transformation m_transformation;
};