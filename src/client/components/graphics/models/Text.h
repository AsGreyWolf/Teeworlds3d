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
	///<param name="text">Text</param>
	///<param name="size">Text size</param>
	///<param name="align">Align (see TextGenerator)</param>
	///<param name="buffering">Buffering (see TextGenerator)</param>
	Text(const std::string& text, int size = 1, int align = 0, bool buffering = false);
	~Text();

	///<summary>Updates generated text with current text</summary>
	///<param name="text">Text</param>
	void SetText(const std::string& text);
	///<summary>Current text</summary>
	std::string text;//TODO: private
	TextGenerator* data;
};

#endif