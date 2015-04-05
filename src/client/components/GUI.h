#ifndef GUI_H
#define GUI_H

#include <vector>
#include "../Component.h"
#include "../../tools/quad2.h"
#include "../../tools/quad3.h"
#include "../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

class Text;

class GUI : Component{
public:
	GUI();
	~GUI();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void StateChange(STATE lastState);
	///<summary>3d render callback</summary>
	void Render();
	///<summary>Render 3d Billboard</summary>
	void RenderBillboard();
	///<summary>2d render callback</summary>
	void Render2d();
	///<summary>Tick callback</summary>
	void Tick();
	///<summary>System message callback</summary>
	void Message(int type,char* value);

	void fill(quad2 in,quad2 out);

	class Text* fpsObject;
	class Text* fpsTitle;
};
GUI* m_GUI();

#endif
