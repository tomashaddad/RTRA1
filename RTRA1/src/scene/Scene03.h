#pragma once

#include "SceneBase.h"
#include "api/Shader.h"

#include "ModernScene.h"

#include <glm/glm.hpp>

#include "Transformation.h"

class Scene03 : public ModernScene {
public:
	Scene03();
	virtual void render() override;
private:
	float m_rotationSpeed;
	std::array<Transformation, 9> m_transformations;
};