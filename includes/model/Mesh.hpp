#pragma once

#include <includes.h>
#include <glm/glm.hpp>
#include <shadering/Shader.hpp>
#include <shadering/VAO.hpp>
#include <model/Vertex.hpp>
#include <model/Texture.hpp>

class Mesh
{
public:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int vao_;

				

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader &shader);

private:
	unsigned int vbo_, ebo_;
	void setupMesh();
};
