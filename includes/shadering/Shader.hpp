#pragma once

#include <includes.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>


class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	~Shader();

	void use();
	
	void setMat4(const std::string& uniformName, const glm::mat4 &value) const;
	void setVec3(const std::string& uniformName, const glm::vec3 &value) const;
	void setUniformBool(const std::string& uniformName, bool value) const;
	void setUniformInt(const std::string& uniformName, int value) const;
	void setUniformFloat(const std::string& uniformName, float value) const;
	void checkCompileErrors(GLuint shader, std::string type);

private:

};
