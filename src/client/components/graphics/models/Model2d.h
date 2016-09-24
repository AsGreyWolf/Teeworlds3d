#ifndef MODEL2D_H
#define MODEL2D_H

#include "../Model.h"
#include <vector>
#define GLEW_STATIC
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#else
#include <glew.h>
#endif
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/geometry/Geometry2d.h>
#include <tools/vmath.h>

class Texture;

class Model2d : public Model {
public:
	Model2d(int type = GL_TRIANGLES);
	Model2d(const Model2d &second);
	~Model2d() override;
	void Render() override;

	Model2d &operator=(const Model2d &second);

	void Add(const Geometry2d &geom);
	void Clear();

	Texture texture;
	glm::vec2 position;
	glm::vec4 color;
	float depth;

protected:
	class Data : public Geometry2d {
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
		GLuint tbuffer;
	};
	using dataPtr = std::shared_ptr<Data>;
	inline dataPtr make_dataPtr() { return std::make_shared<Data>(); }

	dataPtr data;
	int type;
};

#endif
