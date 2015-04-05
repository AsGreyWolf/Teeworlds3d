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
	///<param name="lighting">Use lighting?</param>
	Text3d(bool lighting=false);
	///<summary>Deletes the buffers in the RAM</summary>
	void Clear();
	TextGenerator* data;
	///<summary>Creates generated text data</summary>
	///<param name="text">Text</param>
	///<param name="size">Text size</param>
	///<param name="align">Align (see TextGenerator)</param>
	///<param name="buffering">Buffering (see TextGenerator)</param>
	void AddText(std::string text,int size=1,int align=0,bool buffering=true);
	///<summary>Updates generated text with current text</summary>
	///<param name="text">Text</param>
	void SetText(std::string text);
	std::string text;
};

#endif