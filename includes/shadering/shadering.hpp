#include <includes.h>
#include <fstream>
#include <sstream>

#pragma once

namespace shadering{

	const std::string loadShaderSource(const std::string& filePath);
	
	unsigned int compileVertexShader(const std::string& vertexShaderSource);

	unsigned int compileFragmentShader(const std::string& fragmentShaderSource);

	unsigned int linkShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

}
