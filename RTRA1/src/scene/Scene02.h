#pragma once

#include "SceneBase.h"
#include "api/Shader.h"

#include "ModernScene.h"

class Scene02 : public ModernScene {
public:
	Scene02();
	virtual void init() override;
	virtual void render() override;
};