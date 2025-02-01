#include <shadering/Shader.hpp>
#include <shadering/shadering.hpp>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	this->shaderProgramId = shadering::linkShaderProgram(vertexShaderPath, fragmentShaderPath);
}

void Shader::use() {
	glUseProgram(this->shaderProgramId);
}

void Shader::setUniformBool(const std::string& uniformName, bool value) const{
	glUniform1i(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), (int)value);
}

void Shader::setMat4(const std::string& uniformName, const glm::mat4 &value) const {
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& uniformName, const glm::vec3 &value) const {
	glUniform3fv(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), 1, glm::value_ptr(value));
}

void Shader::setUniformInt(const std::string& uniformName, int value) const {
	glUniform1i(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), value);
}

void Shader::setUniformFloat(const std::string& uniformName, float value) const {
	glUniform1f(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), value);
}

Shader::~Shader() {

}