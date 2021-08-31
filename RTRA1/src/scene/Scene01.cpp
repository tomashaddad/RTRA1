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

	//glEnable(GL_LIGHTING);

	//// directional light source
	//float ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	//float diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	//float specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	//float position0[] = { 1.0, 0.0, 0.0, 0.0 };

	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	//glLightfv(GL_LIGHT0, GL_POSITION, position0);
	//glEnable(GL_LIGHT0);
}

// take index, mod by 36, divide the result by 3

void Scene01::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMultMatrixf((const float*)glm::value_ptr(RTRApp::instance().getCamera()->getViewMatrix()));

	float position0[] = { 1.0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	glPushMatrix();
	glScalef(10.0f, 10.0f, 10.0f);
		glBegin(GL_TRIANGLES);
		for (int index = 0; index < m_indices.size() - 3; index += 3) {
			glVertex3f(m_vertices[m_indices[index + 0]].x, m_vertices[m_indices[index + 0]].y, m_vertices[m_indices[index + 0]].z);
			glVertex3f(m_vertices[m_indices[index + 1]].x, m_vertices[m_indices[index + 1]].y, m_vertices[m_indices[index + 1]].z);
			glVertex3f(m_vertices[m_indices[index + 2]].x, m_vertices[m_indices[index + 2]].y, m_vertices[m_indices[index + 2]].z);
		}
		glEnd();
	glPopMatrix();
}

void Scene01::quit() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
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