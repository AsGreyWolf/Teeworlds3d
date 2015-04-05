#include "Text3d.h"
#include "../Graphics.h"
#include "Resources.h"
#include "TextGenerator.h"

Text3d::Text3d(bool lighting):Model(lighting){}
void Text3d::AddText(std::string text,int size,int align,bool buffering){
	this->text=text;
	data=new TextGenerator(text,size,align,buffering);
	AddQuad(quad3(data->geometry)*100,vec3(0,1,0),quad2(1,1,-1,-1));
	texture=data->texture;
}
void Text3d::SetText(string text){
	if(text==this->text) return;
	this->text=text;
	data->SetText(text);
	texture=data->texture;
}
void Text3d::Clear(){
	delete data;
	Model::Clear();
}