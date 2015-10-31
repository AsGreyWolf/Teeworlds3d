#include "TextGenerator.h"
#include "Resources.h"
#include "StringTexture.h"
#include "../Graphics.h"
#include "../../Client.h"

TextGenerator::TextGenerator(string text,int size,int align,bool buffering){
	float cursize=size*1.0f/ FONT_DIVIDER;
	pixels=1;
	while (pixels<g_Graphics()->to_pixels(cursize))
		pixels<<=1;
	this->buffering=buffering;
	texture=new StringTexture(text, pixels, buffering);
	switch(align){
	case ALIGN_LEFT_TOP:
		geometry=quad2(0,-cursize,cursize*texture->aspect,cursize);
		break;
	case ALIGN_LEFT_CENTER:
		geometry=quad2(0,-cursize/2,cursize*texture->aspect,cursize);
		break;
	case ALIGN_LEFT_BOTTOM:
		geometry=quad2(0,0,cursize*texture->aspect,cursize);
		break;
	case ALIGN_CENTER_TOP:
		geometry=quad2(-cursize/2* texture->aspect,-cursize,cursize*texture->aspect,cursize);
		break;
	case ALIGN_CENTER_CENTER:
		geometry=quad2(-cursize/2* texture->aspect,-cursize/2,cursize*texture->aspect,cursize);
		break;
	case ALIGN_CENTER_BOTTOM:
		geometry=quad2(-cursize/2* texture->aspect,0,cursize*texture->aspect,cursize);
		break;
	case ALIGN_RIGHT_TOP:
		geometry=quad2(-cursize*texture->aspect,-cursize,cursize*texture->aspect,cursize);
		break;
	case ALIGN_RIGHT_CENTER:
		geometry=quad2(-cursize*texture->aspect,-cursize/2,cursize*texture->aspect,cursize);
		break;
	case ALIGN_RIGHT_BOTTOM:
		geometry=quad2(-cursize*texture->aspect,0,cursize*texture->aspect,cursize);
		break;
	}
}
void TextGenerator::SetText(string text){
	delete texture;
	texture=new StringTexture(text, pixels, buffering);
}
TextGenerator::~TextGenerator(){
	delete texture;
}