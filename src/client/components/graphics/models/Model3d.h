#ifndef MODEL3D_H
#define MODEL3D_H

#include "../Model.h"
#include <vector>
#define GLEW_STATIC
#include <glew.h>
#include <tools/vmath.h>
#include <tools/Positioned.h>
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/geometry/Geometry3d.h>

class Model3d : public Model, public Positioned {
public:
	Model3d(bool lighting = true, int type = GL_TRIANGLES);
	Model3d(const Model3d &second);
	virtual ~Model3d() override;
	virtual void Render() override;
	virtual void Enable() override;
	virtual void Disable() override;
	virtual void UpdateMatrix(const glm::mat4 &parentMatrix = glm::mat4(1.0f));

	Model3d &operator=(const Model3d &second);

	void Add(const Geometry3d &geom);
	void ScaleAt(const glm::vec3 &to, const glm::vec3 &basic,
	             const glm::vec3 &additional);

	Texture texture;
	glm::vec3 scale;
	glm::vec4 color;

	glm::mat4 modelMatrix;
	glm::mat4 normalMatrix;

protected:
	class ShadowModel;
	class Data {
	public:
		Data();
		~Data();
		void Validate();
		void Render(int type);
		void Add(const Geometry3d &geom);

	private:
		GLuint vao;
		GLuint vbuffer;
		GLuint nbuffer;
		GLuint tbuffer;
		Geometry3d geometry;
		bool valid = false;
	};
	typedef std::shared_ptr<Data> Model3dDataPtr;
	#define Model3dDataPtr() std::make_shared<Data>()

	Model3dDataPtr data;
	ShadowModel *shadow;
	int type;
	bool light;

	glm::mat4 bufferedModelMatrix;
	glm::vec3 bufferedPos;
	rot3 bufferedRot;
	glm::mat4 bufferedParentMatrix;
};

#endif
