#pragma once

#include <glm/glm.hpp>

struct Material {
	bool beingUsed = false;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	glm::vec3 Ambient;
	float Shininess;
};