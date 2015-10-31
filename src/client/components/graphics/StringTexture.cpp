#include "StringTexture.h"
#include "Resources.h"
#include "../Graphics.h"
#include "../../../shared/Console.h"
using namespace std;

void StringTexture::Initialize(TTF_Font* font, std::string data) {
	buffering=false;
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, data.c_str(), g_Graphics()->m_Resources->SDLColorWhite);
	if (!surface){
		Initialize(g_Graphics()->m_Resources->textureRGB);
		Console::Err("Could not generate text: " + string(SDL_GetError()));
		return;
	}
	Texture::Initialize(surface, true, true);
	SDL_FreeSurface(surface);
};
void StringTexture::Initialize(Texture* t) {
	buffering=true;
	aspect = t->aspect;
	id = (*t);
};
StringTexture::~StringTexture() {
	if (buffering)
		cleanup = false;
};
std::map<int, std::map<std::string, Texture*>> StringTexture::stringBuffer;
StringTexture::StringTexture(std::string data, int size, bool buffering) : buffering(buffering) {
	Initialize(g_Graphics()->m_Resources->textureRGB);
	if (buffering) {
		map<int, map<string, Texture*>>::iterator key = stringBuffer.find(size);
		if (key == stringBuffer.end()) {
			stringBuffer.insert(stringBuffer.begin(), pair<int, map<string, Texture*>>(size, map<string, Texture*>()));
			key = stringBuffer.find(size);
		}
		map<string, Texture*>::iterator datakey = (*key).second.find(data);
		if (datakey == (*key).second.end()) {
			Texture* texture = NULL;
			float aspect = 1;
			TTF_Font* font = g_Graphics()->m_Resources->LoadFont(size);
			if (font != NULL) {
				texture = new StringTexture(font, data);
				(*key).second.insert((*key).second.begin(), pair<string, Texture*>(data, texture));
				datakey = (*key).second.find(data);
			}
		}
		if (datakey != (*key).second.end())
			Initialize((*datakey).second);
	}
	else {
		TTF_Font* font = g_Graphics()->m_Resources->LoadFont(size);
		if (font != NULL) {
			Initialize(font, data);
		}
	}
};
void StringTexture::ClearBuffers() {
	for (map<int, map<string, Texture*>>::iterator key = stringBuffer.begin(); key != stringBuffer.end(); key++) {
		for (map<string, Texture*>::iterator datakey = (*key).second.begin(); datakey != (*key).second.end(); datakey++) {
			delete (*datakey).second;
		}
		(*key).second.clear();
	}
	stringBuffer.clear();
}
