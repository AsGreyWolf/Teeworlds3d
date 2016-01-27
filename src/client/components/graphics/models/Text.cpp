#include "Text.h"
#include "../Resources.h"
#include "../TextGenerator.h"
#include "../../Graphics.h"

Text::Text(const std::string& text, int size, int align, bool buffering):Model2d(){
	this->text = text;
	data = new TextGenerator(text, size, align, buffering);
	texture = data->texture;
	AddQuad(data->geometry, quad2(0, 1, 1, -1));
}
Text::~Text() {
	delete data;
}
void Text::SetText(const string& text){
	if(text==this->text) return;
	this->text=text;
	data->SetText(text);
	texture= data->texture;
}