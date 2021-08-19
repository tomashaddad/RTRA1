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

#define GLT_IMPLEMENTATION
#include "dependencies/gltext.h"

RTRApp* RTRApp::m_instance = nullptr;

RTRApp::RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
	: m_sdlManager(std::make_unique<SDLManager>(title, width, height, fullscreen))
	, m_glManager(std::make_unique<GLManager>())
	, m_inputManager(std::make_unique<InputManager>())
	, m_camera(std::make_unique<Camera>())
	, m_state(State::GOOD)
	, m_currentScene(0)
{
	m_instance = this;

	m_glManager->enableDepthTesting(true);
	m_glManager->cullBackFaces(true);

	// simple scene with cube, lights and text for testing
	m_scenes[0] = std::make_unique<Scene00>();

	// actual scenes for the assignment
	m_scenes[1] = std::make_unique<Scene01>();
	m_scenes[2] = std::make_unique<Scene02>();
	m_scenes[3] = std::make_unique<Scene03>();
	m_scenes[4] = std::make_unique<Scene04>();
	m_scenes[5] = std::make_unique<Scene05>();
	m_scenes[6] = std::make_unique<Scene06>();

	// TODO: PUT THIS SOMEWHERE ELSE?
	const float aspect = static_cast<float>(m_sdlManager->getWindowWidth()) /
						 static_cast<float>(m_sdlManager->getWindowHeight());
	m_camera->setPerspectiveMatrix(45.0f, aspect, 0.1f, 100.0f);

	m_scenes[m_currentScene]->init();
}

void RTRApp::run() {
	while (m_state != State::QUIT) {
		checkInput();
		float dt = m_sdlManager->getFrameDeltaTime();
		updateState(dt);
		renderFrame(dt);
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
			case SDLK_ESCAPE:
				m_state = State::QUIT;
				break;
			case SDLK_w:
				std::cout << "W" << std::endl;
				break;
			}
		}
	}
}

void RTRApp::updateState(float dt) {

}

void RTRApp::renderFrame(float dt) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scenes[m_currentScene]->render();

	m_sdlManager->swapBuffers();
}

const SDLManager* RTRApp::getSDLManager() const {
	return m_sdlManager.get();
}

const GLManager* RTRApp::getGLManager() const {
	return m_glManager.get();
}

const InputManager* RTRApp::getInputManager() const {
	return m_inputManager.get();
}

const Camera* RTRApp::getCamera() const {
	return m_camera.get();
}