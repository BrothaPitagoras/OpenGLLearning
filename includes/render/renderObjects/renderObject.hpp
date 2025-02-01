#pragma once

#include <shadering/VAO.hpp>

class renderObject
{
public:
	std::vector<float> *vertices;
	std::vector<unsigned int> *indices;
	VAO* vertexArrayObject;

	renderObject(VAO* vao, std::vector<float> *vertices, std::vector<unsigned int> *indices, bool normal = false, bool color = false, bool texture = false);
	~renderObject();



private:

};