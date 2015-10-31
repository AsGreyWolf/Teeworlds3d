#ifndef STRINGTEXTURE_H
#define STRINGTEXTURE_H

#include <string>
#include <map>
#include "../../../../other/sdl/include/SDL_ttf.h"
#include "../../../tools/quad2.h"
#include "../../../tools/quad3.h"
#include "../../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../../other/glm/gtc/type_ptr.hpp"
#include "Texture.h"

class StringTexture: public Texture {
public:
	///<summary>Get text texture</summary>
	///<param name="data">Text</param>
	///<param name="size">Text size</param>
	///<param name="buffering">Is buffering enabled</param>
	StringTexture(std::string data, int size, bool buffering);
	~StringTexture();

	static void ClearBuffers();
private:
	bool buffering;
	StringTexture(TTF_Font* font, std::string data){Initialize(font,data);};
	void Initialize(TTF_Font* font, std::string data);
	StringTexture(Texture* t){Initialize(t);};
	void Initialize(Texture* t);

	static std::map<int, std::map<std::string, Texture*>> stringBuffer;
};

#endif
