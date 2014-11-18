#ifndef SPHERE_H
#define SPHERE_H

#include "Model.h"

///<summary>Simple sphere generator</summary>
class Sphere : public Model
{
public:
	///<summary>Creates the model and buffers in the GPU and fill the buffers in the CPU with generated sphere data</summary>
	///<param name="type">Type of the verts (GL_TRIANGLES)</param>
	///<param name="g">Link to the Graphics component</param>
	///<param name="lighting">Use lighting?</param>
	///<param name="rings">Number of rings</param>
	///<param name="sectors">Number of sectors</param>
	///<param name="lengthiness">3-axis deformation</param>
	///<param name="radius">Radius</param>
	///<param name="texcoord">UV coordinates</param>
	///<param name="backstart">Reverse generation</param>
	Sphere(Graphics* g, bool lighting, int rings, int sectors,vec3 lengthiness,float radius,quad2 texcoord,bool backstart);
};

#endif