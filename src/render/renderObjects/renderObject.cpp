#include <render/renderObjects/renderObject.hpp>

renderObject::renderObject(VAO* vao, std::vector<float> vertices) {
	this->vertexArrayObject = vao;
	this->vertices = vertices;
	if (!this->vertices.empty())
	{
		vertexArrayObject->assignAll(&this->vertices, nullptr);
	}
}
renderObject::~renderObject() {

}