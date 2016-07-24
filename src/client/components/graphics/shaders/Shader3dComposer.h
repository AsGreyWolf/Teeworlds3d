#ifndef SHADER3DCOMPOSER_H
#define SHADER3DCOMPOSER_H

#include "ShaderTexture.h"
#include <tools/vmath.h>

class Shader3dComposer : public ShaderTexture {
private:
	Shader3dComposer();
	friend Shader3dComposer *g_Shader3dComposer();

public:
	~Shader3dComposer() override;
	void Render() override;

private:
	GLuint shadowProjectionMatrixUniform;
	GLuint cameraUniform;
};
Shader3dComposer *g_Shader3dComposer();

#endif
