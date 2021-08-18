#pragma once

#include <glad/glad.h>
#include <SDL.h>

#include <string>

#include "SDLManager.h"
#include "GLManager.h"

enum class State {
	GOOD,
	RUN,
	QUIT,
};

class RTRApp {
public:
	RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);

	void run();

	void checkInput();
	void updateState(unsigned int dt);
	void renderFrame(double dt);

protected:
	State m_state;
	SDLManager m_sdlManager;
	GLManager m_glManager;
};