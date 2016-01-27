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
	StringTexture(const std::string& data, int size, bool buffering);
	~StringTexture();

	///<summary>Clean up the buffers</summary>
	static void ClearBuffers();
private:
	///<summary>Generate string texture with spec. font and string data</summary>
	///<param name="font">TTF Font pointer</param>
	///<param name="data">Data string</param>
	StringTexture(TTF_Font* font, const std::string& data) { Initialize(font, data); };
	///<summary>Initialize string texture with spec. font and string data</summary>
	///<param name="font">TTF Font pointer</param>
	///<param name="data">Data string</param>
	void Initialize(TTF_Font* font, const std::string& data);
	///<summary>Generate string texture with spec. texture</summary>
	StringTexture(Texture* t) { Initialize(t); };
	///<summary>Initialize string texture with spec. texture</summary>
	void Initialize(Texture* t);
	///<summary>Is buffering enabled</summary>
	bool buffering;
	///<summary>Buffered data</summary>
	static std::map<int, std::map<std::string, Texture*>> stringBuffer;
};

#endif
