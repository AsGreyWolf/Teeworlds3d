#include "Label.h"
#include <client/components/Graphics.h>
#include <client/components/graphics/Texture.h>

Label::Label(const std::string &str, int size) : Panel() { SetText(str, size); }
Label::Label(const Label &second) : Panel() { *this = second; }
void Label::SetText(const std::string &str, int s) {
	texture = g_TextGenerator()->Generate(str, s, container.w);
	size.y = g_Graphics()->to_screen(model.texture.size.y);
	size.x = size.y * model.texture.aspect;
}
