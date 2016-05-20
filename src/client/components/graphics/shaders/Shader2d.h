#ifndef SHADER2D_H
#define SHADER2D_H

#include "../Shader.h"
#include <tools/vmath.h>

class Shader2d : public Shader {
private:
	Shader2d();
	friend Shader2d *g_Shader2d();

public:
	~Shader2d() override;
	void Render() override;
	void SetColor(const glm::vec4 &color);
	void SetPosition(const glm::vec2 &pos, float depth);

private:
	GLuint colorUniform;
	GLuint aspectUniform;
	GLuint positionUniform;
	GLuint textureUniform;
};
Shader2d *g_Shader2d();

#endif
