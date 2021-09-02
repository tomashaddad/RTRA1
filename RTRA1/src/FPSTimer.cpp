#pragma once

#include "FPSTimer.h"

#include "RTRApp.h"

#include <iostream>

FPSTimer::FPSTimer()
	: m_start(0)
	, m_end(0)
	, m_counter(0)
	, m_runningFps(0)
	, m_averageFps(0) {}

void FPSTimer::start() {
	++m_counter;
	m_start = RTRApp::instance().getSDLManager()->getPerformanceCounter();
}

void FPSTimer::end() {
	m_end = RTRApp::instance().getSDLManager()->getPerformanceCounter();
	m_runningFps += getFPS();
	if (m_counter == 100) {
		m_averageFps = m_runningFps / 100;
		m_counter = 0;
		m_runningFps = 0;
	}
}

const float FPSTimer::getFPS() {
	return 1.0f / ((m_end - m_start) / (float)RTRApp::instance().getSDLManager()->getPerformanceFrequency());
}

const float FPSTimer::getAverageFPS() {
	return m_averageFps;
}