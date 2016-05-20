#ifndef MODEL2D_H
#define MODEL2D_H

#include "../Model.h"
#include <vector>
#define GLEW_STATIC
#include <glew.h>
#include <tools/vmath.h>
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/geometry/Geometry2d.h>

class Texture;

class Model2d : public Model {
public:
	Model2d(int type = GL_TRIANGLES);
	Model2d(const Model2d &second);
	~Model2d() override;
	void Render() override;

	Model2d &operator=(const Model2d &second);

	void Add(const Geometry2d &geom);

	Texture texture;
	glm::vec2 position;
	glm::vec4 color;
	float depth;

protected:
	class Data {
	public:
		Data();
		~Data();
		void Validate();
		void Render(int type);
		void Add(const Geometry2d &geom);

	private:
		GLuint vao;
		GLuint vbuffer;
		GLuint tbuffer;
		Geometry2d geometry;
		bool valid = false;
	};
	typedef std::shared_ptr<Data> Model2dDataPtr;
#define Model2dDataPtr() std::make_shared<Data>()

	Model2dDataPtr data;
	int type;
};

#endif
