#pragma once

class FPSTimer {
public:
	FPSTimer();

	void start();
	void end();
	const float& getAverageFPS();

private:
	const float getFPS();

private:
	unsigned int m_start;
	unsigned int m_end;

	unsigned int m_counter;
	float m_runningFps;
	float m_averageFps;
};