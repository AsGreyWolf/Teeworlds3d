#ifndef SHADERPARTICLE_H
#define SHADERPARTICLE_H

#include "../Shader.h"
#include <tools/vmath.h>

class Texture;

class ShaderParticle : public Shader {
private:
	ShaderParticle();
	friend ShaderParticle *g_ShaderParticle();

public:
	~ShaderParticle() override;
	void Render() override;
	void SetColor(const glm::vec4 &color);
	void SetMatrix(const glm::mat4 &modelMatrix);

private:
	GLuint colorUniform;
	GLuint viewProjectionMatrixUniform;
	GLuint modelMatrixUniform;
	GLuint textureUniform;

	glm::mat4 perspectiveMatrix;
};
ShaderParticle *g_ShaderParticle();

#endif
