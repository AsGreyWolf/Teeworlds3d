#include "Camera.h"
#include <iostream>
#include "Graphics.h"
#include "../Client.h"
#include "../../shared/System.h"

class Camera* pCamera;
Camera* g_Camera(){ return pCamera; }

Camera::Camera() : Component(){
	pCamera = this;
	position = vec3(0, 0, 0);
	rotation = vec3(0, 0, 0);
	SetMatrix();
}
Camera::~Camera(){
	pCamera = NULL;
}
void Camera::Input(unsigned char* keys,int xrel,int yrel,int wheel){
	RotateX(-yrel*g_System()->tickCoeff);
	RotateZ(-xrel*g_System()->tickCoeff);
	/*glm::vec3 look2=look;
	look2*=512;
	look2 *= g_System()->tickCoeff;
	glm::vec3 right2=right;
	right2*=512;
	right2 *= g_System()->tickCoeff;
	glm::vec3 up2=up;
	up2*=512;
	up2 *= g_System()->tickCoeff;
	if (keys[SDL_SCANCODE_W]) position+=look2;
	if (keys[SDL_SCANCODE_S]) position-=look2;
	if (keys[SDL_SCANCODE_D]) position+=right2;
	if (keys[SDL_SCANCODE_A]) position-=right2;
	if (keys[SDL_SCANCODE_R]) position+=up2;
	if (keys[SDL_SCANCODE_F]) position-=up2;*/
}
void Camera::Render(){}
void Camera::RenderBillboard(){}
void Camera::Render2d(){}
void Camera::Tick(){}
void Camera::Message(int type,char* value){}

void Camera::SetMatrix(){
	if (!g_Client()->state.ingame) return;
	updateVectors();

	g_Graphics()->SetViewMatrix(position, position + look, up);

	glScalef(1,1,1);
}
void Camera::RotateX(float rad){
	rotation.x+=rad;
}
void Camera::RotateY(float rad){
	rotation.y+=rad;
}
void Camera::RotateZ(float rad){
	rotation.z+=rad;
}
void Camera::updateVectors(){
	up=vec3(0,0,1);
	up=glm::rotateY(up, rotation.y);
	up=glm::rotateX(up, rotation.x);
	up=glm::rotateZ(up, rotation.z);

	look=vec3(0,1,0);
	look=glm::rotateY(look, rotation.y);
	look=glm::rotateX(look, rotation.x);
	look=glm::rotateZ(look, rotation.z);

	right=vec3(1,0,0);
	right=glm::rotateY(right, rotation.y);
	right=glm::rotateX(right, rotation.x);
	right=glm::rotateZ(right, rotation.z);
}
void Camera::StateChange(STATE lastState){
	if (!lastState.ingame && g_Client()->state.ingame){
		rotation=vec3(0,0,0);
		look=vec3(0,1,0);
		up=vec3(0,0,1);
		position=vec3(0,0,0);
		right=vec3(1,0,0);
		//sinx=0;siny=0;sinz=0;
		//cosx=1;cosy=1;cosz=1;
	}
}
