#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getPerspectiveMatrix() const {
	return m_perspective;
}

void Camera::setPerspectiveMatrix(const float fov, const float aspect, const float near, const float far) {
	m_perspective = glm::perspective(glm::radians(fov), aspect, near, far);
}