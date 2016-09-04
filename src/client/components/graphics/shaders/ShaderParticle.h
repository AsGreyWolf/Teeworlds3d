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
	void SetSize(float size);
	void SetGravity(float gravity);
	void SetTTL(float time);
	void SetVel(const glm::vec3 &vel);

private:
	glm::mat4 perspectiveMatrix;
};
ShaderParticle *g_ShaderParticle();

#endif
