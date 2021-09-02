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
		const unsigned int refreshRate = instance.getSDLManager()->getRefreshRate();
		const unsigned int scene = instance.getCurrentSceneNumber();
		const int width = instance.getSDLManager()->getWindowWidth();
		const int height = instance.getSDLManager()->getWindowHeight();
		const unsigned int maxSubdivisions = instance.getScene()->getMaxSubdivisions();
		const unsigned int verticesSize = instance.getScene()->getVerticesSize();
		const bool depthTesting = instance.getGLManager()->isDepthTesting();
		const bool cullingBackFaces = instance.getGLManager()->isCullingBackFaces();

		text
			<< "Scene: " << scene << std::endl
			<< "Display: " << width << " x " << height << "(" << refreshRate << " Hz)" << std::endl
			<< "FPS: " << fps << std::endl
			<< "Subdivisions: " << maxSubdivisions << std::endl
			<< "Vertices: " << verticesSize << std::endl
			<< "Faces: " << ((verticesSize / 8) * 2 * 6) << std::endl // 8 verts per cube, 2 faces per 6 sides
			<< "Data: " << "Placeholder" << std::endl
			<< "Lighting: " << "Placeholder" << std::endl
			<< "Depth testing: " << fps << std::endl
			<< "Backface culling: " << fps << std::endl;
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