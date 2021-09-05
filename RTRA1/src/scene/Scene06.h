#pragma once

#include "SceneBase.h"
#include "api/Shader.h"

#include "ModernScene.h"

class Scene06 : public ModernScene {
public:
	Scene06();
	virtual void init() override;
	virtual void render() override;
};