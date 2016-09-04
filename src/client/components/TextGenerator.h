#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include "../ClientComponent.h"
#include <SDL_ttf.h>
#include <client/components/graphics/Texture.h>
#include <map>

enum FONTS { FONT_NORMAL = 1, FONT_BIG = 2, FONT_DIVIDER = 40 };
#define WIDTH_INFINITIVE (-1)

class TextGenerator : public ClientComponent {
private:
	TextGenerator();
	friend TextGenerator *g_TextGenerator();

public:
	~TextGenerator() override;

	Texture Generate(const std::string &data, int size = FONT_NORMAL,
	                 float width = WIDTH_INFINITIVE);
	TTF_Font *Font(int size = FONT_NORMAL);

	static const std::string fontPath;
	static const int outline;

private:
	std::map<int, TTF_Font *> fonts;
};
TextGenerator *g_TextGenerator();

#endif
