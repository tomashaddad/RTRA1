#pragma once

#include "SceneBase.h"
#include "api/Shader.h"

class Scene02 : public SceneBase {
public:
	Scene02();
	~Scene02();
	virtual void init() override;
	virtual void render() override;
	virtual void incrementSubdivisions() override;
	virtual void decrementSubdivisions() override;

private:
	void updateLayout();

private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	Shader m_shader;
};

