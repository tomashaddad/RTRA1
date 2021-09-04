#include "Scene01.h"

#include "RTRApp.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>
#include <cmath>
#include "Camera.h"

Scene01::Scene01() {
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0); // one point light
	glEnable(GL_LIGHT7); // and the directional light
}

Scene01::~Scene01() {
	disableEachPointLight();
	glDisable(GL_LIGHT7); // directional light
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
}

void Scene01::init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const int& width = RTRApp::instance().getSDLManager()->getWindowWidth();
	const int& height = RTRApp::instance().getSDLManager()->getWindowHeight();
	const Camera* camera = RTRApp::instance().getCamera();
	perspective(camera->getFOV(), (float)width / (float)height, camera->getNearPlane(), camera->getFarPlane());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	createLights();

	float ambient0[] = { 0.2, 0.2, 0.2, 1.0 };
	float diffuse0[] = { 0.3, 0.3, 0.3, 1.0 };
	float specular0[] = { 0.3, 0.3, 0.3, 1.0 };
	float position0[] = { 0.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
}

void Scene01::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMultMatrixf((const float*)glm::value_ptr(RTRApp::instance().getCamera()->getViewMatrix()));

	updateLightPositions();

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

// I don't want my light manager to have vec4's so ...
void Scene01::createLights() {
	const std::vector<PointLight>& lights = m_lightManager.getPointLights();

	// 7 point lights
	for (int i = 0; i < 7; ++i) {
		float type = m_lightManager.getTypeAsFloat(lights[i]);
		float ambient[] = { lights[i].ambient.x, lights[i].ambient.y, lights[i].ambient.z, type };
		float diffuse[] = { lights[i].diffuse.x, lights[i].diffuse.y, lights[i].diffuse.z, type };
		float specular[] = { lights[i].specular.x, lights[i].specular.y, lights[i].specular.z, type };
		float position[] = { lights[i].position.x, lights[i].position.y, lights[i].position.z, type };
		switch (i) {
		case 0:
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			break;
		case 1:
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT1, GL_POSITION, position);
			break;
		case 2:
			glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT2, GL_POSITION, position);
			break;
		case 3:
			glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT3, GL_POSITION, position);
			break;
		case 4:
			glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT4, GL_POSITION, position);
			break;
		case 5:
			glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT5, GL_POSITION, position);
			break;
		case 6:
			glLightfv(GL_LIGHT6, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT6, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT6, GL_POSITION, position);
			break;
		case 7:
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			break;
		}
	}

	// directional light
	DirectionalLight dlight = m_lightManager.getDirectionalLight();
	float type7 = m_lightManager.getTypeAsFloat(lights[7]);
	float ambient7[] = { dlight.ambient.x, dlight.ambient.y, dlight.ambient.z, type7 };
	float diffuse7[] = { dlight.diffuse.x, dlight.diffuse.y, dlight.diffuse.z, type7 };
	float specular7[] = { dlight.specular.x, dlight.specular.y, dlight.specular.z, type7 };
	float direction7[] = { dlight.direction.x, dlight.direction.y, dlight.direction.z, type7 };
	glLightfv(GL_LIGHT7, GL_AMBIENT, ambient7);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse7);
	glLightfv(GL_LIGHT7, GL_SPECULAR, specular7);
	glLightfv(GL_LIGHT7, GL_POSITION, direction7);
}

void Scene01::updateLightPositions() {
	const std::vector<PointLight>& lights = m_lightManager.getPointLights();

	float type0 = m_lightManager.getTypeAsFloat(lights[0]);
	float position0[] = { lights[0].position.x, lights[0].position.y, lights[0].position.z, type0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	float type1 = m_lightManager.getTypeAsFloat(lights[1]);
	float position1[] = { lights[1].position.x, lights[1].position.y, lights[1].position.z, type1 };
	glLightfv(GL_LIGHT0, GL_POSITION, position1);

	float type2 = m_lightManager.getTypeAsFloat(lights[2]);
	float position2[] = { lights[2].position.x, lights[2].position.y, lights[2].position.z, type2 };
	glLightfv(GL_LIGHT0, GL_POSITION, position2);

	float type3 = m_lightManager.getTypeAsFloat(lights[3]);
	float position3[] = { lights[3].position.x, lights[3].position.y, lights[3].position.z, type3 };
	glLightfv(GL_LIGHT0, GL_POSITION, position3);

	float type4 = m_lightManager.getTypeAsFloat(lights[4]);
	float position4[] = { lights[4].position.x, lights[4].position.y, lights[4].position.z, type4 };
	glLightfv(GL_LIGHT0, GL_POSITION, position4);

	float type5 = m_lightManager.getTypeAsFloat(lights[5]);
	float position5[] = { lights[5].position.x, lights[5].position.y, lights[5].position.z, type5 };
	glLightfv(GL_LIGHT0, GL_POSITION, position5);

	float type6 = m_lightManager.getTypeAsFloat(lights[6]);
	float position6[] = { lights[6].position.x, lights[6].position.y, lights[6].position.z, type6 };
	glLightfv(GL_LIGHT0, GL_POSITION, position6);

	float type7 = m_lightManager.getTypeAsFloat(lights[7]);
	float position7[] = { lights[7].position.x, lights[7].position.y, lights[7].position.z, type7 };
	glLightfv(GL_LIGHT0, GL_POSITION, position7);
}

void Scene01::toggleLighting() {
	SceneBase::toggleLighting();
	if (SceneBase::hasLights()) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}
}


void Scene01::incrementLights() {
	SceneBase::incrementLights();
	setImmediateModeLights();
}

void Scene01::decrementLights() {
	SceneBase::decrementLights();
	setImmediateModeLights();
}

void Scene01::enableEachLight() {
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);
}

void Scene01::disableEachPointLight() {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
}

void Scene01::setImmediateModeLights() {
	disableEachPointLight();
	// GL_LIGHT7 always on because it is directional
	switch (m_lightNumber) {
	case 8:
		enableEachLight();
		break;
	case 7:
		glEnable(GL_LIGHT6);
		[[fallthrough]];
	case 6:
		glEnable(GL_LIGHT5);
		[[fallthrough]];
	case 5:
		glEnable(GL_LIGHT4);
		[[fallthrough]];
	case 4:
		glEnable(GL_LIGHT3);
		[[fallthrough]];
	case 3:
		glEnable(GL_LIGHT2);
		[[fallthrough]];
	case 2:
		glEnable(GL_LIGHT1);
		[[fallthrough]];
	case 1:
		glEnable(GL_LIGHT0);
		break;
	}
}

