#include "Camera.h"

#include <client/components/Input.h>
#include <shared/System.h>

class Camera *pCamera;
Camera *g_Camera() { return pCamera != nullptr ? pCamera : new Camera(); }

Camera::Camera() : ClientComponent(), Positioned() {
	pCamera = this;
	pos = glm::vec3(0.0, 0.0, 0.0);
	rot = rot3(0.0, 0.0, 0.0);
	UpdateVectors();
}
Camera::~Camera() { pCamera = nullptr; }
void Camera::Tick() {
	RotateX(-g_Input()->mouseY * 0.01);
	RotateZ(-g_Input()->mouseX * 0.01);
	UpdateVectors();
}
void Camera::RotateX(float rad) { rot.x += rad; }
void Camera::RotateY(float rad) { rot.y += rad; }
void Camera::RotateZ(float rad) { rot.z += rad; }
void Camera::UpdateVectors() {
	up = glm::rotate(glm::vec3(0.0, 0.0, 1.0), rot);
	look = glm::rotate(glm::vec3(0.0, 1.0, 0.0), rot);
	right = glm::rotate(glm::vec3(1.0, 0.0, 0.0), rot);
}
void Camera::StateChange(const STATE &prevState) {
	ClientComponent::StateChange(prevState);
	if (!prevState.ingame && state.ingame) {
		rot = rot3(0.0, 0.0, 0.0);
		pos = glm::vec3(0.0, 0.0, 0.0);
		UpdateVectors();
	}
}
