#include "Scene02.h"

#include <iostream>

Scene02::Scene02()
	: m_shader("./src/shaders/scene02/menger.vert", "./src/shaders/scene02/menger.frag", "./src/shaders/scene02/menger.geom")
	, m_VAO(0)
	, m_VBO(0) {}

Scene02::~Scene02() {

}

void Scene02::init() {

}

void Scene02::render() {

}