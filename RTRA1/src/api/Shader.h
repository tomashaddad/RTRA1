#pragma once

#include <glad/glad.h>

#include <string>

class Shader {
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader = "", const bool& fromFile = true);
	~Shader();

	bool bind() const;
	void unbind() const;

	GLint getUniform(const std::string& name);
	const GLuint getID() const;

private:
	std::string parseFile(const std::string& file);
	GLuint compileShader(const GLenum& type, const std::string& shader);
	void attachShaderByID(const GLuint id);
	
private:
	bool m_compiled;
	GLuint m_programID;
	GLuint m_vertexID;
	GLuint m_fragmentID;
	GLuint m_geometryID;
};

