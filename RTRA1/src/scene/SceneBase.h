#pragma once

#include <memory>
#include "api/Shader.h"

class SceneBase {
public:
	virtual void init() = 0;
	virtual void render() = 0;

protected:
	unsigned int m_VAO;
	std::unique_ptr<Shader> m_shader;
};