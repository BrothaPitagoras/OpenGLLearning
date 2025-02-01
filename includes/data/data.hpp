#pragma once

#include <includes.h>
#include <glm/glm.hpp>

#ifndef MODEL_NAMESPACE
#define MODEL_NAMESPACE
namespace Model{
	inline float scale_factor = 1.0f;

	inline float model_mov_speed_factor = 2.0f;

	inline glm::vec3 lightPosition_ = glm::vec3(1.2f, 1.0f, 2.0f);

	inline bool control_light = false;
}

#endif
