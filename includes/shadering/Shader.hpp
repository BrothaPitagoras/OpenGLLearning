#include <includes.h>

class Shader
{
public:
	unsigned int shaderProgramId;

	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void use();

	void setUniformBool(const std::string& uniformName, bool value) const;
	void setUniformInt(const std::string& uniformName, int value) const;
	void setUniformFloat(const std::string& uniformName, float value) const;

private:

};
