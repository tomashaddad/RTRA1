#pragma once
#include "SceneBase.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

class Scene01 : public SceneBase {
public:
	Scene01();
	~Scene01();
	virtual void render() override;
	virtual void init() override;
	virtual void toggleLighting() override;
	virtual void incrementLights() override;
	virtual void decrementLights() override;
private:
	void createLights();
	void updateLightPositions();
	void enableEachLight();
	void disableEachPointLight();
	void setImmediateModeLights();
	void perspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};
