#pragma once
#include "SceneBase.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

class Scene01 : public SceneBase {
public:
	~Scene01();
	virtual void render() override;
	virtual void init() override;
private:
	void perspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};
