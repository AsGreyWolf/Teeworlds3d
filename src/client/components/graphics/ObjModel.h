#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <string>
#include "Model.h"

///<summary>OBJ file loader</summary>
class ObjModel : public Model
{
public:
	///<summary>Creates model from OBJ</summary>
	///<param name="g">Link to the Graphics component</param>
	///<param name="lighting">Use lighting?</param>
	///<param name="filename">Path to the file from data folder</param>
	ObjModel(Graphics* g,bool lighting,std::string filename);
};

#endif