#include "SDLManager.h"

#include <glad/glad.h>

#include "GLException.h"

#include <iostream>

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

SDLManager::SDLManager(const std::string& title, int width, int height, bool fullscreen)
	: m_window({ title, width, height, fullscreen })
{
	initialise();
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

SDLManager::~SDLManager() {
	SDL_GL_DeleteContext(m_sdl.context);
	SDL_DestroyWindow(m_sdl.window);
	SDL_Quit();
}

bool SDLManager::initialise() {
	if (!initSDL())
		throw GLException("Failed to initialise SDL", __FILE__, __LINE__);

	if (!initWindow())
		throw GLException("Failed to create window", __FILE__, __LINE__);

	if (!initContext())
		throw GLException("Failed to create OpenGL context", __FILE__, __LINE__);

	if (!initGLAD())
		throw GLException("Failed to initialise GLAD", __FILE__, __LINE__);

	return true;
}

bool SDLManager::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	return true;
}

bool SDLManager::initWindow() {
	if (m_window.fullscreen) {
		m_sdl.window = SDL_CreateWindow(
			m_window.title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			0, 0,
			SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	}
	else {
		m_sdl.window = SDL_CreateWindow(
			m_window.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_window.width, m_window.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	}

	if (m_sdl.window == NULL) {
		return false;
	}

	SDL_GetWindowSize(m_sdl.window, &m_window.width, &m_window.height);

	return true;
}

bool SDLManager::initContext() {
	m_sdl.context = SDL_GL_CreateContext(m_sdl.window);

	if (m_sdl.context == NULL) {
		return false;
	}
	return true;
}

bool SDLManager::initGLAD() {
	return gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
}

void SDLManager::swapBuffers() const {
	SDL_GL_SwapWindow(m_sdl.window);
}

float const SDLManager::getTimeElapsed() {
	m_timer.time = SDL_GetTicks() / 1000.0f;
	return m_timer.time;
}

float const SDLManager::getFrameDeltaTime() {
	m_timer.deltaTime = getTimeElapsed() - m_timer.time;
	return m_timer.deltaTime;
}

const unsigned int SDLManager::getWindowWidth() const {
	return m_window.width;
}

const unsigned int SDLManager::getWindowHeight() const {
	return m_window.height;
}