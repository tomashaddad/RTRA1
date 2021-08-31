#pragma once

#include <glad/glad.h>
#include <SDL.h>

#include <string>
#include <memory>
#include <array>

#include "SDLManager.h"
#include "GLManager.h"

#include "scene/SceneBase.h"

#include "Camera.h"

#include "Text.h"

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

	RTRApp(const std::string& title, unsigned int width = 1280, unsigned int height = 720, bool fullscreen = true);

	void run();

	void checkInput();
	void switchToScene(unsigned int sceneNumber);
	void renderFrame(float dt);
	void quit();

public:
	SDLManager* getSDLManager() const;
	GLManager* getGLManager() const;
	Camera* getCamera() const;
	Text* getText() const;

	const unsigned int& getCurrentSceneNumber() const;

private:
	static RTRApp* m_instance;

	State m_state;

	std::unique_ptr<SDLManager> m_sdlManager;
	std::unique_ptr<GLManager> m_glManager;
	std::unique_ptr<Camera> m_camera;

	unsigned int m_currentSceneNumber;
	std::unique_ptr<SceneBase> m_currentScene;

	std::unique_ptr<Text> m_text;
};