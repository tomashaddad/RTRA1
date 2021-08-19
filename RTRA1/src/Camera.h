#pragma once

#include <glm/glm.hpp>

enum class Axis {
	x,
	y,
	z
};

enum class Direction {
	forward,
	backward
};

class Camera {
public:
	void setPerspectiveMatrix(const float fov, const float aspect, const float near, const float far);
	glm::mat4 getPerspectiveMatrix() const;

private:
	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;

	glm::mat4 m_view;
	glm::mat4 m_perspective;
};