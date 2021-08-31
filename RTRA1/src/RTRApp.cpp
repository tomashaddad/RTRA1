#include "RTRApp.h"

#include <iostream>

#include "GLException.h"
#include "scene/Scene00.h"
#include "scene/Scene01.h"
#include "scene/Scene02.h"
#include "scene/Scene03.h"
#include "scene/Scene04.h"
#include "scene/Scene05.h"
#include "scene/Scene06.h"

RTRApp* RTRApp::m_instance = nullptr;

RTRApp::RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
	: m_sdlManager(std::make_unique<SDLManager>(title, width, height, fullscreen))
	, m_glManager(std::make_unique<GLManager>())
	, m_camera(std::make_unique<Camera>(45.0f, 0.1f, 100.0f))
	, m_state(State::GOOD)
	, m_currentSceneNumber(1)
	, m_currentScene(std::make_unique<Scene00>())
	, m_text(std::make_unique<Text>())
{
	m_instance = this;
}

void RTRApp::run() {
	m_currentScene->init();

	while (m_state != State::QUIT) {
		m_sdlManager->update();

		checkInput();

		float dt = m_sdlManager->getFrameDeltaTime();
		renderFrame(dt);

		m_sdlManager->swapBuffers();
	}
}

void RTRApp::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_state = State::QUIT;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_0:
					switchToScene(0);
					break;
				case SDLK_1:
					switchToScene(1);
					break;
				case SDLK_2:
					switchToScene(2);
					break;
				case SDLK_3:
					switchToScene(3);
					break;
				case SDLK_4:
					switchToScene(4);
					break;
				case SDLK_5:
					switchToScene(5);
					break;
				case SDLK_6:
					switchToScene(6);
					break;
				case SDLK_w:
					getCamera()->moveForward();
					break;
				case SDLK_s:
					getCamera()->moveBackward();
					break;
				case SDLK_a:
					getCamera()->rollLeft();
					break;
				case SDLK_c:
					getGLManager()->toggleBackFaceCulling();
					break;
				case SDLK_d:
					getCamera()->rollRight();
					break;
				case SDLK_h:
					getText()->toggleFPSMode();
					break;
				case SDLK_z:
					getGLManager()->toggleDepthTesting();
					break;
				case SDLK_ESCAPE:
					m_state = State::QUIT;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				getCamera()->yaw(event.motion.xrel);
				getCamera()->pitch(event.motion.yrel);
				break;
		}
	}
}

void RTRApp::switchToScene(unsigned int sceneNumber) {
	if (m_currentSceneNumber == sceneNumber) {
		return; // do not re-render the same scene
	}

	switch (sceneNumber) {
	case 0:
		m_currentScene = std::make_unique<Scene00>();
		break;
	case 1:
		m_currentScene = std::make_unique<Scene01>();
		break;
	case 2:
		m_currentScene = std::make_unique<Scene02>();
		break;
	case 3:
		m_currentScene = std::make_unique<Scene03>();
		break;
	case 4:
		m_currentScene = std::make_unique<Scene04>();
		break;
	case 5:
		m_currentScene = std::make_unique<Scene05>();
		break;
	case 6:
		m_currentScene = std::make_unique<Scene06>();
		break;
	}

	m_currentSceneNumber = sceneNumber;
	m_currentScene->init();
}

void RTRApp::renderFrame(float dt) {
	m_text->render();
	m_currentScene->render();
}

void RTRApp::quit() {
	m_state = State::QUIT;
	gltTerminate();
}

SDLManager* RTRApp::getSDLManager() const {
	return m_sdlManager.get();
}

GLManager* RTRApp::getGLManager() const {
	return m_glManager.get();
}

Camera* RTRApp::getCamera() const {
	return m_camera.get();
}

Text* RTRApp::getText() const {
	return m_text.get();
}

const unsigned int& RTRApp::getCurrentSceneNumber() const {
	return m_currentSceneNumber;
}