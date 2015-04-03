#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "Model2d.h"

class Graphics;
class TextGenerator;

///<summary>2d text model</summary>
class Text : public Model2d
{
public:
	///<summary>Creates the model and buffers in the GPU and fill the buffers in the CPU with generated text data</summary>
	Text();
	///<summary>Deletes the buffers in the RAM</summary>
	void clear();
	TextGenerator* data;
	///<summary>Creates generated text data</summary>
	///<param name="text">Text</param>
	///<param name="size">Text size</param>
	///<param name="align">Align (see TextGenerator)</param>
	///<param name="buffering">Buffering (see TextGenerator)</param>
	void addText(std::string text,int size=1,int align=0,bool buffering=true);
	///<summary>Updates generated text with current text</summary>
	///<param name="text">Text</param>
	void setText(std::string text);
	std::string text;
};

#endif