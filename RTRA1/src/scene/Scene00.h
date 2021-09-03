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
	virtual void incrementSubdivisions() {} // not needed in sandbox
	virtual void decrementSubdivisions() {} // not needed in sandbox

private:
	unsigned int m_VBO;
	unsigned int m_cubeVAO;
	unsigned int m_lightCubeVAO;
	Shader m_cubeShader;
	Shader m_lightShader;
};