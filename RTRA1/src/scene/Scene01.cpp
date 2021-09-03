#include "Scene01.h"

#include "RTRApp.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>
#include <cmath>
#include "Camera.h"

Scene01::~Scene01() {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
}

void Scene01::init() {
	const int& width = RTRApp::instance().getSDLManager()->getWindowWidth();
	const int& height = RTRApp::instance().getSDLManager()->getWindowHeight();

	const Camera* camera = RTRApp::instance().getCamera();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(camera->getFOV(), (float)width / (float)height, camera->getNearPlane(), camera->getFarPlane());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);

	//const std::vector<PointLight>& lights = m_lightManager.getPointLights();

	//glLightfv(GL_LIGHT0, GL_AMBIENT, &lights[0].ambient[0]);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, &lights[0].diffuse[0]);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, &lights[0].specular[0]);
	//glLightfv(GL_LIGHT0, GL_POSITION, &lights[0].position[0]);

	float ambient0[] = { 0.2, 0.2, 0.2, 1.0 };
	float diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	float position0[] = { 5.0, 0.0, 5.0, 1.0 };
	// 0 directional, 1 point

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);
	//glEnable(GL_LIGHT4);
	//glEnable(GL_LIGHT5);
	//glEnable(GL_LIGHT6);
	//glEnable(GL_LIGHT7);

	glEnable(GL_NORMALIZE);
}

void Scene01::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// TODO: Fix light moving with camera?
	//float position0[] = { 5.0, 0.0, 5.0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glMultMatrixf((const float*)glm::value_ptr(RTRApp::instance().getCamera()->getViewMatrix()));

	glPushMatrix();
		glBegin(GL_TRIANGLES);
		for (int index = 0; index <= m_menger.indices.size() - 3; index += 3) {
			glm::vec3& p1 = m_menger.vertices[m_menger.indices[index + 0]];
			glm::vec3& p2 = m_menger.vertices[m_menger.indices[index + 1]];
			glm::vec3& p3 = m_menger.vertices[m_menger.indices[index + 2]];
			glm::vec3 normal = glm::normalize(glm::triangleNormal(p1, p2, p3));

			if (abs(normal.x) == 1) {
				m_materialManager.setMaterial(MaterialName::RUBY);
			}
			else if (abs(normal.y) == 1) {
				m_materialManager.setMaterial(MaterialName::EMERALD);
			}
			else if (abs(normal.z) == 1) {
				m_materialManager.setMaterial(MaterialName::TURQUOISE);
			}

			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glVertex3f(p3.x, p3.y, p3.z);
		}
		glEnd();
	glPopMatrix();
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