#ifndef MODEL3D_H
#define MODEL3D_H

#include "../Model.h"
#include <vector>
#define GLEW_STATIC
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#else
#include <glew.h>
#endif
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/geometry/Geometry3d.h>
#include <tools/Positioned.h>
#include <tools/vmath.h>

class Model3d : public Model, public Positioned {
public:
	explicit Model3d(bool lighting = true, int type = GL_TRIANGLES);
	Model3d(const Model3d &second);
	virtual ~Model3d() override;
	virtual void Render() override;
	virtual void Enable() override;
	virtual void Disable() override;
	virtual void UpdateMatrix(const glm::mat4 &parentMatrix = glm::mat4(1.0f));

	Model3d &operator=(const Model3d &second);

	void Add(const Geometry3d &geom);
	void Clear();
	void ScaleAt(const glm::vec3 &to, const glm::vec3 &basic,
	             const glm::vec3 &additional);

	Texture texture;
	glm::vec3 scale;
	glm::vec4 color;

	glm::mat4 modelMatrix;
	glm::mat4 normalMatrix;

protected:
	class ShadowModel;
	class Data : public Geometry3d {
	public:
		Data();
		~Data();
		void Invalidate();
		void Render(int type);

	private:
		void Validate();
		bool valid = false;
		GLuint vao;
		GLuint vbuffer;
		GLuint nbuffer;
		GLuint tbuffer;
	};
	using dataPtr = std::shared_ptr<Data>;
	inline dataPtr make_dataPtr() { return std::make_shared<Data>(); }

	dataPtr data;
	ShadowModel *shadow;
	int type;
	bool light;

	glm::mat4 bufferedModelMatrix;
	glm::vec3 bufferedPos;
	rot3 bufferedRot;
	glm::mat4 bufferedParentMatrix;
};

#endif
