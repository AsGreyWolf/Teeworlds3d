#include "TextGenerator.h"
#include "../Graphics.h"
#include "Resources.h"

TextGenerator::TextGenerator(Graphics* g,string text,int size,int align,bool buffering){
	m_Graphics=g;
	float aspect=1;
	float cursize=size*1.0f/m_Graphics->m_Resources->FONT_DIVIDER;
	pixels=1;
	while(pixels<m_Graphics->to_pixels(cursize))
		pixels<<=1;
	this->buffering=buffering;
	m_Graphics->m_Resources->loadStringTexture(texture,aspect,text,pixels,buffering);
	switch(align){
	case ALIGN_LEFT_TOP:
		geometry=quad2(0,-cursize,cursize*aspect,cursize);
		break;
	case ALIGN_LEFT_CENTER:
		geometry=quad2(0,-cursize/2,cursize*aspect,cursize);
		break;
	case ALIGN_LEFT_BOTTOM:
		geometry=quad2(0,0,cursize*aspect,cursize);
		break;
	case ALIGN_CENTER_TOP:
		geometry=quad2(-cursize/2*aspect,-cursize,cursize*aspect,cursize);
		break;
	case ALIGN_CENTER_CENTER:
		geometry=quad2(-cursize/2*aspect,-cursize/2,cursize*aspect,cursize);
		break;
	case ALIGN_CENTER_BOTTOM:
		geometry=quad2(-cursize/2*aspect,0,cursize*aspect,cursize);
		break;
	case ALIGN_RIGHT_TOP:
		geometry=quad2(-cursize*aspect,-cursize,cursize*aspect,cursize);
		break;
	case ALIGN_RIGHT_CENTER:
		geometry=quad2(-cursize*aspect,-cursize/2,cursize*aspect,cursize);
		break;
	case ALIGN_RIGHT_BOTTOM:
		geometry=quad2(-cursize*aspect,0,cursize*aspect,cursize);
		break;
	}
}
void TextGenerator::setText(string text){
	float aspect=1;
	if(!buffering)
		m_Graphics->m_Resources->unLoadTexture(texture);
	m_Graphics->m_Resources->loadStringTexture(texture,aspect,text,pixels,buffering);
}
TextGenerator::~TextGenerator(){
	if(!buffering)
		m_Graphics->m_Resources->unLoadTexture(texture);
}