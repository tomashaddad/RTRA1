#pragma once

#include "SceneBase.h"
#include "api/Shader.h"

//#include <memory>

class ModernScene : public SceneBase {
public:
	ModernScene(Shader shader);
	virtual ~ModernScene();
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void incrementSubdivisions() override;
	virtual void decrementSubdivisions() override;

protected:
	void updateLayout();
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	Shader m_shader;
};