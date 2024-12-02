#pragma once

#include <shadering/VAO.hpp>

class renderObject
{
public:
	std::vector<float> vertices;
	VAO* vertexArrayObject;

	renderObject(VAO* vao, std::vector<float> vertices);
	~renderObject();



private:

};