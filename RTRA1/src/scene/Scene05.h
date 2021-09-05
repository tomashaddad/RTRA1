#pragma once

#include "ModernScene.h"

class Scene05 : public ModernScene {
public:
	Scene05();
	virtual void init() override;
	virtual void render() override;
private:
	virtual void updateLayout() override;
	void sendVerticesToBuffer();
	std::vector<glm::vec3> m_transformedVertices;
};