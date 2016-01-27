#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
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
	Model(bool lighting=true, bool isBillboard=false, int type = GL_TRIANGLES);
	///<summary>Fills the buffers in the GPU with values in the RAM</summary>
	virtual void Create();
	///<summary>Pushes the model into the shader</summary>
	virtual void Render();
	///<summary>Deletes the buffers in the RAM</summary>
	virtual void Clear();
	virtual ~Model();
	///<summary>Update matrix</summary>
	virtual void SetMatrix(const glm::mat4& parent = mat4(1.0f));
	

	///<summary>Appends vector of vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="n">Vertex normals</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddVertex(const std::vector<glm::vec3>& v, const std::vector<glm::vec3>& n, const std::vector<glm::vec2>& t);
	///<summary>Appends 1 vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex position</param>
	///<param name="n">Vertex normal</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddVertex(const glm::vec3& v, const glm::vec3& n, const glm::vec2& t);
	///<summary>Appends 1 quad to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="n">Vertex normal</param>
	///<param name="t">Vertex UV coordinates</param>
	void AddQuad(const quad3& v, const glm::vec3& n, const quad2& t);
	///<summary>Add generated sphere data in the buffers</summary>
	///<param name="rings">Number of rings</param>
	///<param name="sectors">Number of sectors</param>
	///<param name="lengthiness">3-axis deformation</param>
	///<param name="radius">Radius</param>
	///<param name="texcoord">UV coordinates</param>
	///<param name="backstart">Reverse generation</param>
	void AddSphere(const vec3& position, int rings, int sectors, const vec3& lengthiness, float radius, const quad2& texcoord, bool backstart);
	///<summary>Add generated data in the buffers from the OBJ file</summary>
	///<param name="filename">Path to the file from data folder</param>
	void AddObjModel(const vec3& position, const std::string& filename);
	///<summary>Add generated rounded-rectangle data in the buffers</summary>
	///<param name="in">Inner space</param>
	///<param name="out">Outer space</param>
	void AddRectangle(const quad2& in, const quad2& out, float depth = 0);
	///<summary>Rotates Model to the specific direction</summary>
	///<param name="to">Position of object to look to</param>
	void LookAt(const vec3& to);
	///<summary>Scale by vector</summary>
	///<param name="to">Position of object to scale to</param>
	///<param name="basic">Basic scale</param>
	///<param name="additional">Scale per vector length</param>
	void ScaleAt(const vec3& to, const vec3& basic, const vec3& additional);

	///<summary>Texture used in shaders</summary>
	Texture* texture;
	///<summary>Position of the model</summary>
	glm::vec3 position;
	///<summary>Ratation of the model</summary>
	glm::vec3 rotation;
	///<summary>Scale of the model</summary>
	glm::vec3 scale;
	///<summary>Color of the model</summary>
	///If alpha>0 this color will recolor the model(color replacement), otherwise texture color will be multiplied with this value
	glm::vec4 color;

	///<summary>Calculated modelMatrix</summary>
	glm::mat4 modelMatrix;
	///<summary>Calculated normalMatrix</summary>
	glm::mat4 normalMatrix;

	///<summary>Render all registred models</summary>
	static void RenderModels();
	///<summary>Render all registred billboard</summary>
	static void RenderBillboards();
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
	const int type;
	///<summary>If model is billboard model</summary>
	const bool isBillboard;
	///<summary>Use lighting?</summary>
	bool lighting;
private:
	///<summary>Registred models list</summary>
	static std::list<Model*> registredModels;
	///<summary>Registred billboards list</summary>
	static std::list<Model*> registredBillboards;
};

#endif
