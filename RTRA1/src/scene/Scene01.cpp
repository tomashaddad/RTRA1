#include "Scene01.h"

#include "RTRApp.h"

#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

void Scene01::init() {
	const int& width = RTRApp::instance().getSDLManager()->getWindowWidth();
	const int& height = RTRApp::instance().getSDLManager()->getWindowHeight();

	const Camera* camera = RTRApp::instance().getCamera();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(camera->getFOV(), (float)width / (float)height, camera->getNearPlane(), camera->getFarPlane());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Scene01::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((const float*)glm::value_ptr(RTRApp::instance().getCamera()->getViewMatrix()));

	glPointSize(10);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
}

void Scene01::quit() {

}

// From https://stackoverflow.com/questions/12943164/replacement-for-gluperspective-with-glfrustrum
void Scene01::perspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}