#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../../../../tools/quad2.h"
#include "../../../../tools/quad3.h"
#include "../../../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../../../other/glm/gtc/type_ptr.hpp"

class Graphics;
class Texture;

///<summary>3d Model object</summary>
class Model{
public:
	///<summary>Creates the model and buffers in the GPU</summary>
	///<param name="type">Type of the verts (GL_TRIANGLES)</param>
	///<param name="lighting">Use lighting?</param>
	Model(bool lighting=true, int type = GL_TRIANGLES);
	///<summary>Fills the buffers in the GPU with values in the RAM</summary>
	virtual void Create();
	///<summary>Pushes the model into the shader</summary>
	virtual void Render(const glm::mat4 &parentMatrix);
	///<summary>Deletes the buffers in the RAM</summary>
	virtual void Clear();
	virtual ~Model();
	virtual void Render() {
		Render(glm::mat4(1.0f));
	}

	///<summary>Appends vector of vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="n">Vertex normals</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddVertex(std::vector<glm::vec3> v,std::vector<glm::vec3> n,std::vector<glm::vec2> t);
	///<summary>Appends 1 vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex position</param>
	///<param name="n">Vertex normal</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddVertex(glm::vec3 v,glm::vec3 n,glm::vec2 t);
	///<summary>Appends 1 quad to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="n">Vertex normal</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddQuad(quad3 v,glm::vec3 n,quad2 t);
	///<summary>Add generated sphere data in the buffers</summary>
	///<param name="rings">Number of rings</param>
	///<param name="sectors">Number of sectors</param>
	///<param name="lengthiness">3-axis deformation</param>
	///<param name="radius">Radius</param>
	///<param name="texcoord">UV coordinates</param>
	///<param name="backstart">Reverse generation</param>
	void AddSphere(int rings, int sectors,vec3 lengthiness,float radius,quad2 texcoord,bool backstart);
	///<summary>Add generated data in the buffers from the OBJ file</summary>
	///<param name="filename">Path to the file from data folder</param>
	void AddObjModel(std::string filename);
	///<summary>Add generated rounded-rectangle data in the buffers</summary>
	///<param name="in">Inner space</param>
	///<param name="out">Outer space</param>
	void AddRectangle(quad2 in, quad2 out, float depth = 0);
	///<summary>Rotates Model to the specific direction</summary>
	///<param name="to">Position of object to look to</param>
	void LookAt(vec3 to);
	///<summary>Scale by vector</summary>
	///<param name="to">Position of object to scale to</param>
	///<param name="basic">Basic scale</param>
	///<param name="additional">Scale per vector length</param>
	void ScaleAt(vec3 to,vec3 basic, vec3 additional);

	///<summary>Texture used in shaders</summary>
	Texture* texture;
	///<summary>Position of the model</summary>
	glm::vec3 position;
	///<summary>Ratation of the model</summary>
	glm::vec3 rotation;
	///<summary>Scale of the model</summary>
	glm::vec3 scale;
	glm::vec4 color;

	glm::mat4 modelMatrix;
	glm::mat4 normalMatrix;
protected:
	///<summary>Vertex positions buffer in the RAM</summary>
	std::vector <glm::vec3> vertex;
	///<summary>Vertex normals buffer in the RAM</summary>
	std::vector <glm::vec3> normal;
	///<summary>Vertex UV coordinates buffer in the RAM</summary>
	std::vector <glm::vec2> texcoord;
	///<summary>Vertex array object</summary>
	GLuint vao;
	///<summary>Vertex positions buffer in the GPU</summary>
	GLuint vbuffer;
	///<summary>Vertex normals buffer in the GPU</summary>
	GLuint nbuffer;
	///<summary>Vertex UV coordinates buffer in the GPU</summary>
	GLuint tbuffer;
	///<summary>Type of the model (GL_TRIANGLES)</summary>
	int type;
	///<summary>Use lighting?</summary>
	bool lighting;
};

#endif
