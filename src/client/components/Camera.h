#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include "../../../other/glew/include/glew.h"
#include "../../../other/glm/gtx/rotate_vector.hpp"
#include "../Component.h"

///<summary>Camera component</summary>
class Camera : public Component{
public:
	///<summary>Vector directed upwards the camera</summary>
	glm::vec3 up;
	///<summary>Vector directed forward the camera</summary>
	glm::vec3 look;
	///<summary>Position of the camera</summary>
	glm::vec3 position;
	///<summary>Vector directed to the right of the camera</summary>
	glm::vec3 right;
	///<summary>Rotation of the camera</summary>
	glm::vec3 rotation;

	///<summary>Stores 'c' to 'm_Client'</summary>
	Camera(Client* c) : Component(c){};
	///<summary>Initialization callback</summary>
	///<returns>true if all right, false if error found</returns>
	bool OnInit();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void OnInput(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void OnStateChange(STATE lastState);
	///<summary>Quit callback</summary>
	void OnQuit();
	///<summary>3d render callback</summary>
	void OnRender();
	///<summary>Render 3d Billboard</summary>
	void OnRenderBillboard();
	///<summary>2d render callback</summary>
	void OnRender2d();
	///<summary>Tick callback</summary>
	void OnTick();
	///<summary>System message callback</summary>
	void OnMessage(int type,char* value);

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
};

#endif