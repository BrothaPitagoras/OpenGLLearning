#include <render/Camera.hpp>

Camera::Camera(
	glm::vec3 position,
	glm::vec3 up,
	float yaw, float pitch
) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	Camera::UpdateCameraVectors();
}

Camera::Camera(
	float posX, float posY, float posZ,
	float upX, float upY, float upZ,
	float yaw = YAW, float pitch = PITCH
) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	Camera::UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = this->MovementSpeed * deltaTime;
	if (direction == UP)
		Position += Up * velocity;
	if (direction == DOWN)
		Position -= Up * velocity;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	// Update front right and up vectors of camera
	Camera::UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	Front = glm::normalize(front);
	// we have front, now calculate right and up vectors of camera
	
	Right = glm::normalize(glm::cross(Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));

}