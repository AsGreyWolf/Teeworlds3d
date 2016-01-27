#ifndef CAMERA_H
#define CAMERA_H

#include "../Component.h"
#define GLM_FORCE_RADIANS
#include "../../../other/glew/include/glew.h"
#include "../../../other/glm/gtx/rotate_vector.hpp"

///<summary>Camera component</summary>
class Camera : public Component{
public:
	Camera();
	~Camera();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void StateChange(const STATE& lastState);

	///<summary>Updates the current viewProjection matrix</summary>
	void SetMatrix();
	///<summary>Rotates the camera</summary>
	///<param name="rad">Angle in radians</param>
	void RotateX(float rad);
	///<summary>Rotates the camera</summary>
	///<param name="rad">Angle in radians</param>
	void RotateY(float rad);
	///<summary>Rotates the camera</summary>
	///<param name="rad">Angle in radians</param>
	void RotateZ(float rad);
	///<summary>Updates the vectors</summary>
	void updateVectors();

	///<summary>Vector directed upwards the camera</summary>
	glm::vec3 up;
	///<summary>Vector directed forward the camera</summary>
	glm::vec3 look;
	///<summary>Vector directed to the right of the camera</summary>
	glm::vec3 right;
	///<summary>Position of the camera</summary>
	glm::vec3 position;
	///<summary>Rotation of the camera</summary>
	glm::vec3 rotation;
};
Camera* g_Camera();

#endif