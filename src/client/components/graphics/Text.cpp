#include "Text.h"
#include "../Graphics.h"
#include "Resources.h"
#include "TextGenerator.h"

Text::Text():Model2d(){}
void Text::AddText(std::string text,int size,int align,bool buffering){
	this->text=text;
	data=new TextGenerator(text,size,align,buffering);
	AddQuad(data->geometry,quad2(0,1,1,-1));
	texture=data->texture;
}
void Text::SetText(string text){
	if(text==this->text) return;
	this->text=text;
	data->SetText(text);
	texture=data->texture;
}
void Text::Clear(){
	delete data;
	Model2d::Clear();
}