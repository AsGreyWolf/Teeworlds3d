#include "TextGenerator.h"
#include <client/components/Graphics.h>
#include <shared/Console.h>
#include <shared/System.h>

class TextGenerator *pTextGenerator;
TextGenerator *g_TextGenerator() {
	return pTextGenerator != nullptr ? pTextGenerator : new TextGenerator();
}

const std::string TextGenerator::fontPath = "font.ttf";
const int TextGenerator::outline = 1;

TextGenerator::TextGenerator() : ClientComponent() {
	pTextGenerator = this;
	if (TTF_Init() != 0) {
		g_Console()->Err("Unable to initialize SDL_TTF: " +
		                 std::string(TTF_GetError()));
		return; // TODO: need exceptions
	}
	SDL_version ver = *TTF_Linked_Version();
	g_Console()->Info("Initialized SDL_TTF " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
}
TextGenerator::~TextGenerator() {
	for (auto &font : fonts) {
		TTF_CloseFont(font.second);
	}
	TTF_Quit();
	pTextGenerator = nullptr;
}
Texture TextGenerator::Generate(const std::string &data, int size,
                                float width) {
	Texture texture;
	TTF_Font *font = Font(size);
	if (font != nullptr) {
		TTF_SetFontOutline(font, 0);
		int w = width == 0 ? INT_MAX : g_Graphics()->to_pixels(width);
		SDL_Surface *surface = TTF_RenderUTF8_Blended_Wrapped(
		    font, data.c_str(), SDL_Color{255, 255, 255, 255},
		    w); // TODO: fix shadow wrapping
		TTF_SetFontOutline(font, outline);
		SDL_Surface *shadowSurface = TTF_RenderUTF8_Blended_Wrapped(
		    font, data.c_str(), SDL_Color{96, 96, 96, 255}, w);
		if (surface != nullptr && shadowSurface != nullptr) {
			SDL_Rect dest;
			dest.x = outline;
			dest.y = outline;
			dest.w = surface->w;
			dest.h = surface->h;
			SDL_BlitSurface(surface, nullptr, shadowSurface, &dest);
			texture = Texture(shadowSurface);
		}
		if (surface != nullptr) {
			SDL_FreeSurface(surface);
		}
		if (shadowSurface != nullptr) {
			SDL_FreeSurface(shadowSurface);
		}
	}
	return texture;
}
TTF_Font *TextGenerator::Font(int size) {
	auto key = fonts.find(size);
	if (key != fonts.end()) {
		return key->second;
	}
	int pt = 1;
	while (pt < g_Graphics()->to_pixels(size * 1.0f / FONT_DIVIDER)) {
		pt <<= 1;
	}
	TTF_Font *font = TTF_OpenFont(g_System()->GetDataFile(fontPath).c_str(), pt);
	if (font == nullptr) {
		g_Console()->Err("Error Loading Font: " + fontPath + "(" +
		                 std::to_string(size) + ") : " + std::string(TTF_GetError()));
		return font;
	}
	fonts[size] = font;
	g_Console()->Info("Font loaded " + fontPath);
	return font;
}
