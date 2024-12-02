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

void Shader::setUniformInt(const std::string& uniformName, int value) const {
	glUniform1i(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), value);
}

void Shader::setUniformFloat(const std::string& uniformName, float value) const {
	glUniform1i(glGetUniformLocation(this->shaderProgramId, uniformName.c_str()), value);
}

Shader::~Shader() {

}