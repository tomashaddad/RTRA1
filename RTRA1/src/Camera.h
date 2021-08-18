#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	static Camera& getInstance() {
		static Camera camera;
		return camera;
	}

	void setPerspectiveMatrix(const float fov, const float aspect, const float near, const float far);
	glm::mat4 getPerspectiveMatrix() const;

private:
	glm::mat4 m_view;
	glm::mat4 m_perspective;
};