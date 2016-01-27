#ifndef TEXT3D_H
#define TEXT3D_H

#include <string>
#include "Model.h"

class Graphics;
class TextGenerator;

///<summary>3d text model</summary>
class Text3d : public Model
{
public:
	///<summary>Creates the model and buffers in the GPU</summary>
	///<param name="text">Text</param>
	///<param name="size">Text size</param>
	///<param name="align">Align (see TextGenerator)</param>
	///<param name="buffering">Buffering (see TextGenerator)</param>
	///<param name="lighting">Use lighting?</param>
	Text3d(const std::string& text, int size = 1, int align = 0, bool buffering = false, bool lighting = false, bool isBillboard = true);
	~Text3d();

	///<summary>Updates generated text with current text</summary>
	///<param name="text">Text</param>
	void SetText(const std::string& text);
	///<summary>Current text</summary>
	std::string text;//TODO private
	TextGenerator* data;
};

#endif