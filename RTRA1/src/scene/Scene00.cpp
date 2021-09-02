#include "Scene00.h"

#include <glad/glad.h>

#include "RTRApp.h"
#include "api/Shader.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Scene00::Scene00()
    : m_VBO(0)
    , m_cubeVAO(0)
    , m_lightCubeVAO(0)
    , m_cubeShader("./src/shaders/scene00/cube.vert", "./src/shaders/scene00/cube_blinnphong.frag")
    , m_lightShader("./src/shaders/scene00/lighting.vert", "./src/shaders/scene00/lighting.frag") {}

Scene00::~Scene00() {
    std::cout << "Scene00 destructor called!" << std::endl;
}

void Scene00::init() {
    // these vertices are from the book; their winding order is wrong
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &m_lightCubeVAO);
    glBindVertexArray(m_lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Scene00::render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = RTRApp::instance().getCamera()->getViewMatrix();
    glm::mat4 projection = RTRApp::instance().getCamera()->getProjectionMatrix();

    m_cubeShader.bind();
    m_cubeShader.setMat4("model", model);
    m_cubeShader.setMat4("view", view);
    m_cubeShader.setMat4("projection", projection);
    m_cubeShader.setVec3f("viewPos", RTRApp::instance().getCamera()->getPosition());

    m_cubeShader.setVec3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    m_cubeShader.setVec3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    m_cubeShader.setVec3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_cubeShader.setFloat("material.shininess", 32.0f);

    glm::vec3 lightPos(0.5f, 1.0f, 1.5f);
    m_cubeShader.setVec3f("light.position", lightPos);
    m_cubeShader.setVec3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_cubeShader.setVec3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_cubeShader.setVec3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    glBindVertexArray(m_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    m_lightShader.bind();
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    m_lightShader.setMat4("model", model);
    m_lightShader.setMat4("view", view);
    m_lightShader.setMat4("projection", projection);

    glBindVertexArray(m_lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}