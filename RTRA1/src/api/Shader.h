#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader = "", const bool& fromFile = true);
	~Shader();

	bool bind() const;
	void unbind() const;

	const GLuint getID() const;

	GLint getUniformLocation(const std::string& uniformName);
	void setInt(const std::string& uniformName, int value);
	void setFloat(const std::string& uniformName, float value);
	void setVec2f(const std::string& uniformName, const glm::vec2& value);
	void setVec3f(const std::string& uniformName, const glm::vec3& value);
	void setVec4f(const std::string& uniformName, const glm::vec4& value);
	void setMat3(const std::string& uniformName, const glm::mat3& matrix);
	void setMat4(const std::string& uniformName, const glm::mat4& matrix);

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

