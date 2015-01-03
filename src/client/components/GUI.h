#ifndef GUI_H
#define GUI_H

#include <vector>
#include "../Component.h"
#include "../../tools/quad2.h"
#include "../../tools/quad3.h"
#include "../../../other/glew/include/glew.h"
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

class Text;

class GUI : Component{
public:
	///<summary>Stores 'c' to 'm_Client'</summary>
	GUI(Client* c) : Component(c){};
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

	void fill(quad2 in,quad2 out);

	class Text* fpsObject;
	class Text* fpsTitle;
};
#endif