#include "RTRApp.h"
#include "GLException.h"

#include <iostream>

RTRApp::RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
	: m_sdlManager(title, width, height, fullscreen)
	, m_state(State::GOOD)
{
	m_glManager.enableDepthTesting(true);
	m_glManager.cullBackFaces(true);
}

void RTRApp::run() {
	while (m_state != State::QUIT) {
		checkInput();
		float dt = m_sdlManager.getFrameDeltaTime();
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
			}
		}
	}
}

void RTRApp::updateState(unsigned int dt) {

}

void RTRApp::renderFrame(double dt) {
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_sdlManager.swapBuffers();
}