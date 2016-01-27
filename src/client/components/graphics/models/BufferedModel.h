#ifndef BUFFEREDMODEL_H
#define BUFFEREDMODEL_H

#include <string>
#include "Model.h"

class Graphics;

///<summary>Buffered(single allready generated) model renderer</summary>
class BufferedModel : public Model
{
public:
	///<summary>Creates the model and buffers in the GPU</summary>
	///<param name="model">Text</param>
	BufferedModel(Model* model);
	~BufferedModel();
	///<summary>Pushes the model into the shader</summary>
	void Render();
	///<summary>Already generated GPU for instanced rendering</summary>
	Model* model;
};

#endif
