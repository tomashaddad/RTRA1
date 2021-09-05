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
	const unsigned int fps = static_cast<unsigned int>(instance.getFPSTimer()->getAverageFPS());

	if (m_fpsMode) {
		text << fps << " FPS";
	}
	else {
		unsigned int refreshRate = instance.getSDLManager()->getRefreshRate();
		unsigned int scene = instance.getCurrentSceneNumber();
		int width = instance.getSDLManager()->getWindowWidth();
		int height = instance.getSDLManager()->getWindowHeight();
		unsigned int maxSubdivisions = instance.getScene()->getMaxSubdivisions();
		unsigned int verticesSize = instance.getScene()->getVerticesSize();
		// every vertex is made up of 3 4-byte floats
		// calculate this before multipling if scene 3 or 4
		unsigned int data = verticesSize * 12; 
		bool hasLighting = instance.getScene()->hasLights();
		bool depthTesting = instance.getGLManager()->isDepthTesting();
		bool cullingBackFaces = instance.getGLManager()->isCullingBackFaces();

		if (instance.getCurrentSceneNumber() == 3 || instance.getCurrentSceneNumber() == 4) {
			verticesSize *= 9;
		}

		text
			<< "Scene: " << scene << std::endl
			<< "Display: " << width << " x " << height << " (" << refreshRate << " Hz)" << std::endl
			<< "FPS: " << fps << std::endl
			<< "Subdivisions: " << maxSubdivisions << std::endl
			<< "Vertices: " << verticesSize << std::endl
			<< "Faces: " << ((verticesSize / 8) * 2 * 6) << std::endl // 8 verts per cube, 2 faces per 6 sides
			<< "Data: " << data << " bytes" << std::endl
			<< "Lighting: " << (hasLighting ? "On" : "Off") << std::endl
			<< "Depth testing: " << (depthTesting ? "On" : "Off") << std::endl
			<< "Backface culling: " << (cullingBackFaces ? "On" : "Off") << std::endl;
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