#pragma once
#include "SceneBase.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

class Scene01 : public SceneBase {
public:
	virtual void render() override;
	virtual void init() override;
	virtual void quit() override;
private:
	void perspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};

