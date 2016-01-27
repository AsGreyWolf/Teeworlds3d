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

///<summary>GUI renderer</summary>
class GUI : Component{
public:
	GUI();
	~GUI();
	///<summary>Tick callback</summary>
	void Tick();
private:
	void Fill(const quad2& in, const quad2& out);

	class Text* fpsObject;
	class Text* fpsTitle;
};
GUI* g_GUI();

#endif
