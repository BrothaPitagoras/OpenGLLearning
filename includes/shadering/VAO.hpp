#pragma once

#include <includes.h>

class VAO
{
public:
	//When you bind a Vertex Array Object, subsequent bindings of Vertex Buffer Objects and Attribs are stored inside the VAO until you unbind it
	unsigned int vao_;
	unsigned int vbo_;
	unsigned int ebo_;
	
	VAO();
	~VAO();

	void assignAll(std::vector<float>* vertices, std::vector<int>* indices);

	// We only need to change the vertices due to previously already assigning everything (attribs and maybe element buffer object)
	void assignVertices(std::vector<float>& vertices);

	void assignIndices(std::vector<int>& indices);

	// Basically makes sure the data used inside VAO is the one being used to DRAW
	void bind();

private:

};