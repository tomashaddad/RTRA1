#pragma once
#include "SceneBase.h"

#include <memory>
#include "api/Shader.h"

class Scene00 : public SceneBase {
public:
	Scene00();
	~Scene00();
	virtual void render() override;
	virtual void init() override;
	virtual void quit() override;
private:
	unsigned int VBO;
	unsigned int cubeVAO;
	unsigned int lightCubeVAO;
	Shader m_cubeShader;
	Shader m_lightShader;
};