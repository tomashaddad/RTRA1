#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	static Camera& getInstance() {
		static Camera camera;
		return camera;
	}

	void setAspectRatio(const float aspect);

private:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_aspect;
};