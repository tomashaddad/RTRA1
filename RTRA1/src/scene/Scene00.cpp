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
    : VBO(0)
    , cubeVAO(0)
    , lightCubeVAO(0)
    , m_cubeShader("./src/shaders/scene00/cube.vert", "./src/shaders/scene00/cube.frag")
    , m_lightShader("./src/shaders/scene00/lighting.vert", "./src/shaders/scene00/lighting.frag") {}


Scene00::~Scene00() {
    std::cout << "Destructor called!" << std::endl;
}

void Scene00::init() {
    m_cubeShader = Shader("./src/shaders/scene00/cube.vert", "./src/shaders/scene00/cube.frag");
    m_lightShader = Shader("./src/shaders/scene00/lighting.vert", "./src/shaders/scene00/lighting.frag");

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

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Scene00::render() {
    m_cubeShader.bind();
    m_cubeShader.setMat4("model", glm::mat4(1.0f));
    m_cubeShader.setMat4("VP", RTRApp::instance().getCamera()->getViewProjectionMatrix());
    m_cubeShader.setVec3f("viewPos", RTRApp::instance().getCamera()->getPosition());

    m_cubeShader.setVec3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    m_cubeShader.setVec3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    m_cubeShader.setVec3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_cubeShader.setFloat("material.shininess", 32.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    m_cubeShader.setVec3f("light.position", lightPos);
    m_cubeShader.setVec3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_cubeShader.setVec3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_cubeShader.setVec3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    m_lightShader.bind();
    m_lightShader.setMat4("VP", RTRApp::instance().getCamera()->getViewProjectionMatrix());
    glm::mat4 model(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    m_lightShader.setMat4("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Scene00::quit() {

}