#include <shadering/VAO.hpp>


void VAO::assignAll(std::vector<float>* vertices, std::vector<int>* indices) {
	//Bind vertex array object (from now on what we do with buffer is being stored inside VAO until we unbind)
	glBindVertexArray(vao_);
	// Copy our vertices array to inside GL_ARRAY_BUFFER (binded to VBO)
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(vertices->front()), &vertices->front(), GL_STATIC_DRAW);

	// Copy our indices array to inside GL_ELEMENT_BUFFER (binded to EBO)
	if (indices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(vertices->front()), &vertices->front(), GL_STATIC_DRAW);
	}
	// set our vertex attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

// We only need to change the vertices due to previously already assigning everything (attribs and maybe element buffer object)
void VAO::assignVertices(std::vector<float>& vertices) {
	// Bind vertex array object (from now on what we do with buffer is being stored inside VAO until we unbind)
	glBindVertexArray(vao_);
	// Copy our vertices array to inside GL_ARRAY_BUFFER (binded to VBO)
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
}

void VAO::assignIndices(std::vector<int>& indices) {
	// Bind vertex array object (from now on what we do with buffer is being stored inside VAO until we unbind)
	glBindVertexArray(vao_);

	// Copy our indices array to inside GL_ELEMENT_BUFFER (binded to EBO)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
}

// Basically makes sure the data used inside VAO is the one being used to DRAW
void VAO::bind() {
	glBindVertexArray(vao_);
}

VAO::VAO() {
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);
	glGenVertexArrays(1, &vao_);
}

VAO::~VAO() {
	glBindVertexArray(0);
	glDeleteVertexArrays(vao_, &vao_);
	glDeleteBuffers(vbo_, &vbo_);
	glDeleteBuffers(ebo_, &ebo_);
}