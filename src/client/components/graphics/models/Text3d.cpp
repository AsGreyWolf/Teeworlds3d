#include "Text3d.h"
#include "../Resources.h"
#include "../TextGenerator.h"
#include "../../Graphics.h"

Text3d::Text3d(const std::string& text, int size, int align, bool buffering,bool lighting, bool isBillboard):Model(lighting, isBillboard), data(NULL){
	this->text = text;
	data = new TextGenerator(text, size, align, buffering);
	texture = data->texture;
	AddQuad(quad3(data->geometry) * 100, vec3(0, 1, 0), quad2(1, 1, -1, -1));
}
Text3d::~Text3d() {
	delete data;
}
void Text3d::SetText(const string& text){
	if(text==this->text) return;
	this->text=text;
	data->SetText(text);
	texture= data->texture;
}