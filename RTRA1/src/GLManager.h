#pragma once

#include <glad/glad.h>

class GLManager {
public:
	void enableDepthTesting(bool enable);
	void cullBackFaces(bool cull);

private:
	bool m_depthTesting = false;
	bool m_cullingBackFace = false;
};