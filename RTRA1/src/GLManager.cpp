#include "GLManager.h"

#include <iostream>

void GLManager::enableDepthTesting(bool enable) {
    if (enable && !m_depthTesting) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        m_depthTesting = true;
    } else if (!enable && m_depthTesting) {
        glDisable(GL_DEPTH_TEST);
        m_depthTesting = false;
    }
}

void GLManager::cullBackFaces(bool cull) {
    if (cull && !m_cullingBackFace) {
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CCW);
        glDisable(GL_CULL_FACE);
        m_cullingBackFace = true;
    } else if (!cull && m_cullingBackFace) {
        glDisable(GL_CULL_FACE);
        m_cullingBackFace = false;
    }
}