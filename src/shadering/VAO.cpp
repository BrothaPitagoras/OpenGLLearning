//#include <shadering/VAO.hpp>


//void VAO::assignAll(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
//	//Bind vertex array object (from now on what we do with buffer is being stored inside VAO until we unbind)
//	glBindVertexArray(vao_);
//	// Copy our vertices array to inside GL_ARRAY_BUFFER (binded to VBO)
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//	// Copy our indices array to inside GL_ELEMENT_BUFFER (binded to EBO)
//	if (!indices.empty())
//	{
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//	}
//
//	// vertex positions
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	// vertex normals
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//	// vertex texture coords
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//	// vertex tangent
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
//	// vertex bitangent
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
//	// ids
//	glEnableVertexAttribArray(5);
//	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
//	// weights
//	glEnableVertexAttribArray(6);
//	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
//
//	glBindVertexArray(0);
//}


// Basically makes sure the data used inside VAO is the one being used to DRAW
//void VAO::bind() {
//	glBindVertexArray(vao_);
//}
//
////void VAO::unbind() {
////	glBindVertexArray(0);
////}
//
//VAO::VAO() {
//	glGenBuffers(1, &vbo_);
//	glGenBuffers(1, &ebo_);
//	glGenVertexArrays(1, &vao_);
//}
//
//VAO::~VAO() {
//	glBindVertexArray(0);
//	glDeleteVertexArrays(vao_, &vao_);
//	glDeleteBuffers(vbo_, &vbo_);
//	glDeleteBuffers(ebo_, &ebo_);
//}