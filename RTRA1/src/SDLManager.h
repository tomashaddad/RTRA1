#pragma once

#include <SDL.h>

#include <string>

struct Timer {
	float time = 0;
	float deltaTime = 0;
};

struct Window {
	const std::string title;
	int width;
	int height;
	bool fullscreen;
};

struct SDL {
	SDL_Window* window;
	SDL_GLContext context;
};

class SDLManager
{
public:
	SDLManager(const std::string& title, int width, int height, bool fullscreen);
	~SDLManager();
	bool initialise();

	void swapBuffers() const;

public:
	const float getTimeElapsed();
	const float getFrameDeltaTime();

	const unsigned int getWindowWidth() const;
	const unsigned int getWindowHeight() const;

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

