#pragma once

#include <includes.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Shader
{
public:
	unsigned int shaderProgramId;

	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void use();
	
	void setMat4(const std::string& uniformName, const glm::mat4 &value) const;
	void setVec3(const std::string& uniformName, const glm::vec3 &value) const;
	void setUniformBool(const std::string& uniformName, bool value) const;
	void setUniformInt(const std::string& uniformName, int value) const;
	void setUniformFloat(const std::string& uniformName, float value) const;

private:

};
