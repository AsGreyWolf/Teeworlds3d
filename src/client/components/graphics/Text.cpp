#include "Text.h"
#include "../Graphics.h"
#include "Resources.h"
#include "TextGenerator.h"

Text::Text(Graphics* g):Model2d(g){}
void Text::addText(std::string text,int size,int align,bool buffering){
	this->text=text;
	data=new TextGenerator(m_Graphics,text,size,align,buffering);
	addQuad(data->geometry,quad2(0,1,1,-1));
	texture=data->texture;
}
void Text::setText(string text){
	if(text==this->text) return;
	this->text=text;
	data->setText(text);
	texture=data->texture;
}
void Text::clear(){
	delete data;
	Model2d::clear();
}