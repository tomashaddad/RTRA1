#pragma once

#include "SceneBase.h"
#include "api/Shader.h"

#include "ModernScene.h"

#include <glm/glm.hpp>

#include "Transformation.h"

class Scene04 : public ModernScene {
public:
	Scene04();
	virtual void init() override;
	virtual void render() override;
private:
	float m_rotationSpeed;
	std::array<Transformation, 9> m_transformations;
};