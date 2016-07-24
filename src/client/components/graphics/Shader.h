#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <list>
#include <set>
#include <memory>
#define GLEW_STATIC
#ifdef __ANDROID__
	#include <GLES3/gl3.h>
#else
	#include <glew.h>
#endif
#include <tools/vmath.h>

class Model;

enum SHADER_BINDINGS { SHADER_POS = 0, SHADER_TEXMAP, SHADER_NORMAL };

class Shader {
protected:
	Shader(const std::string &filepath, glm::vec2 viewport, GLenum culling,
	       GLboolean colormask0, GLboolean colormask1, GLboolean colormask2,
	       GLboolean colormask3, GLboolean depthmask, GLbitfield clear);
	virtual void Render();

public:
	virtual ~Shader();
	inline operator GLuint() const { return id; };

	void RegisterModel(Model *model);
	void UnregisterModel(Model *model);

private:
	GLuint id;

protected:
	GLenum culling;
	GLboolean colormask[4];
	GLboolean depthmask;
	GLbitfield clear;
	glm::vec2 viewport;
	GLuint framebuffer = 0;
	std::set<Model *> registredModels;

public:
	static void RenderShaders();
	static void ClearShaders();

private:
	static std::list<Shader *> registred;
};

#endif
