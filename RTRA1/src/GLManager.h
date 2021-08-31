#pragma once

#include <glad/glad.h>

class GLManager {
public:
	GLManager();
	void toggleDepthTesting();
	void toggleBackFaceCulling();

private:
	bool m_depthTesting;
	bool m_cullBackFace;
};