#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "Model2d.h"

class Graphics;

///<summary>Simple text generator</summary>
class Text : public Model2d
{
public:
	///<summary>Creates the model and buffers in the GPU and fill the buffers in the CPU with generated text data</summary>
	///<param name="type">Type of the verts (GL_TRIANGLES)</param>
	///<param name="g">Link to the Graphics component</param>
	///<param name="text">Text</param>
	///<param name="size">Text size</param>
	Text(Graphics* g,std::string text,int size,int align,bool buffering);
	///<summary>Removes the model</summary>
	void remove();
	///<summary>Updates model with current text</summary>
	///<param name="text">Text</param>
	void setText(std::string text);

	quad2 geometry;
	enum{
		ALIGN_LEFT_TOP=0,
		ALIGN_LEFT_CENTER,
		ALIGN_LEFT_BOTTOM,
		ALIGN_CENTER_TOP,
		ALIGN_CENTER_CENTER,
		ALIGN_CENTER_BOTTOM,
		ALIGN_RIGHT_TOP,
		ALIGN_RIGHT_CENTER,
		ALIGN_RIGHT_BOTTOM,
	};
private:
	int pixels;
	bool buffering;
};

#endif