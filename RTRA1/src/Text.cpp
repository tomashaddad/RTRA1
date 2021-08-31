#include "Text.h"

#include <sstream>

#include <iostream>

#include "RTRApp.h"

Text::Text()
	: m_fpsMode(false)
	, m_xpos(20.0f)
	, m_ypos(20.0f)
	, m_size(2.0f)
{
	gltInit();
	m_text = gltCreateText();
}

void Text::update() const {
	std::stringstream text;

	const RTRApp& instance = RTRApp::instance();
	const unsigned int& fps = instance.getSDLManager()->getFPS();

	if (m_fpsMode) {
		text << fps << " FPS";
	}
	else {
		const unsigned int& scene = instance.getCurrentSceneNumber();
		const int& width = instance.getSDLManager()->getWindowWidth();
		const int& height = instance.getSDLManager()->getWindowHeight();

		text
		<< "Scene: "	<< scene << std::endl
		<< "Display: "  << width << " x " << height << "(" << fps << " Hz)" << std::endl;

	}

	gltSetText(m_text, text.str().c_str());
}

Text::~Text() {
	gltDeleteText(m_text);
	gltTerminate();
}

void Text::render() const {
	update();

	gltBeginDraw();
	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	gltDrawText2D(m_text, m_xpos, m_ypos, m_size);
	gltEndDraw();
}

void Text::toggleFPSMode() {
	m_fpsMode = !m_fpsMode;
}