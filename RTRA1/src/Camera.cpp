#include "RTRApp.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera(float fov, float near, float far)
	: m_fov(fov)
	, m_near(near)
	, m_far(far)
	, m_position(glm::vec3(0.0f))
	, m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}

void Camera::moveForward() {
	m_position += m_rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

void Camera::moveBackward() {
	m_position += m_rotation * glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::yaw(signed int degree) {
	m_rotation *= glm::angleAxis(-(float)degree * 0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::pitch(signed int degree) {
	m_rotation *= glm::angleAxis(-(float)degree * 0.001f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::rollLeft() {
	m_rotation *= glm::angleAxis(glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::rollRight() {
	m_rotation *= glm::angleAxis(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::reset() {
	m_position = glm::vec3(0.0f);
	m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

glm::vec3 Camera::getPosition() const {
	return m_position;
}

glm::mat4 Camera::getViewMatrix() const {
	auto mat4rotation = glm::toMat4(glm::inverse(m_rotation));
	auto translation = glm::translate(glm::mat4(1.0f), m_position + glm::vec3(0.0, 0.0, -10.0f));
	return mat4rotation * translation;
}

glm::mat4 Camera::getProjectionMatrix() const {
	float width = static_cast<float>(RTRApp::instance().getSDLManager()->getWindowWidth());
	float height = static_cast<float>(RTRApp::instance().getSDLManager()->getWindowHeight());
	return glm::perspective(glm::radians(m_fov), width / height, m_near, m_far);
}

glm::mat4 Camera::getViewProjectionMatrix() const {
	return getProjectionMatrix() * getViewMatrix();
}

const float& Camera::getFOV() const {
	return m_fov;
}

const float& Camera::getNearPlane() const {
	return m_near;
}

const float& Camera::getFarPlane() const {
	return m_far;
}