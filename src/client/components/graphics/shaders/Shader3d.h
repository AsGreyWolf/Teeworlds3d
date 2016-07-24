#ifndef SHADER3D_H
#define SHADER3D_H

#include "../Shader.h"
#include <tools/vmath.h>
#include <client/components/graphics/Texture.h>

class Shader3d : public Shader {
private:
	Shader3d();
	friend Shader3d *g_Shader3d();

public:
	~Shader3d() override;
	void Render() override;
	void SetLight(const bool light);
	void SetColor(const glm::vec4 &color);
	void SetMatrix(const glm::mat4 &modelMatrix, const glm::mat4 &normalMatrix);

	Texture color;
	Texture position;
	Texture normal;
	Texture depth;

private:
	GLuint colorUniform;
	GLuint lightUniform;
	GLuint viewProjectionMatrixUniform;
	GLuint modelMatrixUniform;
	GLuint normalMatrixUniform;
	GLuint textureUniform;

	glm::mat4 perspectiveMatrix;
};
Shader3d *g_Shader3d();

#endif
