#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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
	Camera(float fov, float near, float far);

	void moveForward();
	void moveBackward();
	void rollLeft();
	void rollRight();
	void yaw(signed int degree);
	void pitch(signed int degree);

	glm::vec3 getPosition() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewProjectionMatrix() const;

private:
	float m_fov;
	float m_near;
	float m_far;

	glm::quat m_rotation;
	glm::vec3 m_position;
};