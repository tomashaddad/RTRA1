#pragma once

#include <SDL.h>

#include <string>

struct Timer {
	float time = 0;
	float deltaTime = 0;
};

struct Window {
	const std::string title;
	unsigned int width;
	unsigned int height;
	bool fullscreen;
};

struct SDL {
	SDL_Window* window;
	SDL_GLContext context;
};

class SDLManager
{
public:
	SDLManager(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);
	~SDLManager();
	bool initialise();

	void swapBuffers() const;

	float const getTimeElapsed();
	float const getFrameDeltaTime();

private:
	bool initSDL();
	bool initWindow();
	bool initContext();
	bool initGLAD();

private:
	Window m_window;
	Timer m_timer;
	SDL m_sdl;
};

