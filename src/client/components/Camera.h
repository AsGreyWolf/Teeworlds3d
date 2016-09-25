#ifndef CAMERA_H
#define CAMERA_H

#include "../ClientComponent.h"
#include <tools/Positioned.h>
#include <tools/vmath.h>

class Camera : public ClientComponent, public Positioned {
private:
	Camera();
	friend Camera *g_Camera();

public:
	~Camera() override;
	void Tick() override;
	void StateChange(const STATE &prevState) override;

	void UpdateVectors();
	void RotateX(float rad);
	void RotateY(float rad);
	void RotateZ(float rad);

	glm::vec3 up;
	glm::vec3 look;
	glm::vec3 right;
};
Camera *g_Camera();

#endif
