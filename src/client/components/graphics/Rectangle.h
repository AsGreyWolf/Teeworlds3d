#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Model2d.h"

///<summary>Simple rectangle generator</summary>
class Rectangle : public Model2d
{
public:
	///<summary>Creates the model and buffers in the GPU and fill the buffers in the CPU with generated rounded rectangle data</summary>
	///<param name="g">Link to the Graphics component</param>
	Rectangle(Graphics* g,quad2 in,quad2 out);
};
#endif