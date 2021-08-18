#pragma once

#include <glad/glad.h>
#include <SDL.h>

#include <string>
#include <memory>
#include <array>

#include "SDLManager.h"
#include "GLManager.h"

#include "scene/SceneBase.h"

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
	void updateState(float dt);
	void renderFrame(float dt);

private:
	unsigned int m_currentScene;
	State m_state;
	SDLManager m_sdlManager;
	GLManager m_glManager;

	std::array<std::unique_ptr<SceneBase>, 6> m_scenes;
};