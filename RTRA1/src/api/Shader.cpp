#include "Shader.h"

#include <vector>
#include <fstream>
#include <iostream>

Shader::Shader(const char* vertexShader, const char* fragmentShader, const char* geometryShader, const bool& fromFile)
	: m_programID(0)
	, m_vertexID(0)
	, m_fragmentID(0)
	, m_geometryID(0)
	, m_compiled(false)
{
	std::string vs;
	std::string fs;
	std::string gs;

	if (fromFile) {
		vs = parseFile(vertexShader);
		fs = parseFile(fragmentShader);
		if (geometryShader) {
			gs = parseFile(geometryShader);
		}
	} else {
		vs = vertexShader;
		fs = fragmentShader;
		if (geometryShader) {
			gs = geometryShader;
		}
	}

	m_programID = glCreateProgram();
	m_vertexID = compileShader(GL_VERTEX_SHADER, vs);
	m_fragmentID = compileShader(GL_FRAGMENT_SHADER, fs);
	if (geometryShader) {
		m_geometryID = compileShader(GL_GEOMETRY_SHADER, gs);
	}

	attachShaderByID(m_vertexID);
	attachShaderByID(m_fragmentID);
	if (geometryShader) {
		attachShaderByID(m_geometryID);
	}

	glLinkProgram(m_programID);

	GLint linkResult;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE) {
		GLsizei infoLength;
		glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &infoLength);
		std::vector<char> message(infoLength);
		glGetProgramInfoLog(m_programID, infoLength, &infoLength, &message[0]);
		std::cerr << &message[0] << std::endl;

		glDeleteProgram(m_programID);
	}
	else
	{
		glValidateProgram(m_programID);
		m_compiled = true;
	}

	glDetachShader(m_programID, m_vertexID);
	glDeleteShader(m_vertexID);

	glDetachShader(m_programID, m_fragmentID);
	glDeleteShader(m_fragmentID);

	if (geometryShader != nullptr) {
		glDetachShader(m_programID, m_geometryID);
		glDeleteShader(m_geometryID);
	}
}

GLuint Shader::compileShader(const GLenum& type, const std::string& shader) {
	GLuint shaderID = glCreateShader(type);
	if (shaderID) {
		const char* cStrShader = shader.c_str();
		glShaderSource(shaderID, 1, &cStrShader, nullptr);
		glCompileShader(shaderID);

		GLsizei compileResult;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == GL_FALSE) {
			GLsizei infoLength;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLength);
			std::vector<char> message(infoLength);
			glGetShaderInfoLog(shaderID, infoLength, &infoLength, &message[0]);
			std::cerr << &message[0] << std::endl;
			return 0;
		}
	}
	return shaderID;
}

void Shader::attachShaderByID(const GLuint id) {
	if (id != 0) {
		glAttachShader(m_programID, id);
	}
}

std::string Shader::parseFile(const char* file) {
	if (!file) {
		return "";
	}

	std::ifstream stream(file);

	if (!stream.is_open()) {
		std::cerr << "Shader " << file << " could not be opened." << std::endl;
		return "";
	}

	return std::string(
		(std::istreambuf_iterator<char>(stream)),
		(std::istreambuf_iterator<char>())
	);
}

Shader::~Shader() {
	glDeleteProgram(m_programID);
}

bool Shader::bind() const {
	if (m_compiled) {
		glUseProgram(m_programID);
	}
	return m_compiled;
}

void Shader::unbind() const {
	glUseProgram(0);
}

GLint Shader::getUniform(const std::string& name) {
	return GLint();
}

const GLuint Shader::getID() const {
	return m_programID;
}
