#include <render/renderObjects/renderObject.hpp>

renderObject::renderObject(VAO* vao, std::vector<float> vertices, std::vector<unsigned int> indices,  bool color, bool texture) {
	this->vertexArrayObject = vao;
	this->vertices = vertices;
	this->indices = indices;
	int stride = 3 + (color * 3) + (texture * 2);
	int texStart = 3 + (color * 3);
	if (!this->vertices.empty())
	{
		vertexArrayObject->assignAll(&this->vertices, &this->indices, stride);
	}
	if (color)
	{
		// set our vertex attribs
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	if (texture)
	{
		// set our vertex attribs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(texStart * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
}


renderObject::~renderObject() {

}