#ifndef SHADERSHADOW_H
#define SHADERSHADOW_H

#include "../Shader.h"
#include <client/components/graphics/Texture.h>
#include <tools/vmath.h>

class Texture;

class ShaderShadow : public Shader {
private:
	ShaderShadow();
	friend ShaderShadow *g_ShaderShadow();

public:
	~ShaderShadow() override;
	void Render() override;
	void SetMatrix(const glm::mat4 &modelMatrix);
	glm::mat4 matrix;
	Texture shadowMap;

private:
	glm::mat4 orthoMatrix;
};
ShaderShadow *g_ShaderShadow();

#endif
