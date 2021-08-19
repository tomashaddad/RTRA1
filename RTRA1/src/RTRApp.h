#pragma once

#include <glad/glad.h>
#include <SDL.h>

#include <string>
#include <memory>
#include <array>

#include "SDLManager.h"
#include "GLManager.h"
#include "InputManager.h"

#include "scene/SceneBase.h"

#include "Camera.h"

enum class State {
	GOOD,
	RUN,
	QUIT,
};

class RTRApp {
public:
	static RTRApp& instance() {
		return *m_instance;
	}

	RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);

	void run();

	void checkInput();
	void updateState(float dt);
	void renderFrame(float dt);

public:
	const SDLManager* getSDLManager() const;
	const GLManager* getGLManager() const;
	const InputManager* getInputManager() const;
	const Camera* getCamera() const;

private:
	static RTRApp* m_instance;

	State m_state;
	unsigned int m_currentScene;

	std::unique_ptr<SDLManager> m_sdlManager;
	std::unique_ptr<GLManager> m_glManager;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<Camera> m_camera;

	std::array<std::unique_ptr<SceneBase>, 7> m_scenes;
};