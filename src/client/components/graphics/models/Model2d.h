#ifndef MODEL2D_H
#define MODEL2D_H

#include <vector>
#include "../../../../tools/quad2.h"
#include "../../../../tools/quad3.h"
#include "../../../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../../../other/glm/gtc/type_ptr.hpp"

class Graphics;
class Texture;

///<summary>2d Model object</summary>
class Model2d{
public:
	///<summary>Creates the model and buffers in the GPU</summary>
	///<param name="type">Type of the verts (GL_TRIANGLES)</param>
	Model2d(int type = GL_TRIANGLES);
	///<summary>Fills the buffers in the GPU with values in the RAM</summary>
	virtual void Create();
	///<summary>Pushes the model into the shader</summary>
	virtual void Render();
	///<summary>Deletes the buffers in the RAM</summary>
	virtual void Clear();
	virtual ~Model2d();

	///<summary>Appends vector of vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddVertex(std::vector<glm::vec2> v,std::vector<glm::vec2> t);
	///<summary>Appends 1 vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex position</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddVertex(glm::vec2 v,glm::vec2 t);
	///<summary>Appends 1 quad to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddQuad(quad2 v,quad2 t);
	///<summary>Add generated rounded-rectangle data in the buffers</summary>
	///<param name="in">Inner space</param>
	///<param name="out">Outer space</param>
	void AddRectangle(quad2 in,quad2 out);

	///<summary>Texture used in shaders</summary>
	Texture* texture;
	///<summary>Position of the model</summary>
	glm::vec2 position;
	///<summary>Color of the model</summary>
	glm::vec4 color;
	///<summary>Depth of the model</summary>
	float depth;
protected:
	///<summary>Vertex positions buffer in the RAM</summary>
	std::vector <glm::vec2> vertex;
	///<summary>Vertex UV coordinates buffer in the RAM</summary>
	std::vector <glm::vec2> texcoord;
	///<summary>Vertex array object</summary>
	GLuint vao;
	///<summary>Vertex positions buffer in the GPU</summary>
	GLuint vbuffer;
	///<summary>Vertex UV coordinates buffer in the GPU</summary>
	GLuint tbuffer;
	///<summary>Type of the model (GL_TRIANGLES)</summary>
	int type;
};

#endif
