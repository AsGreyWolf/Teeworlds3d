#ifndef SHADER3DCOMPOSER_H
#define SHADER3DCOMPOSER_H

#include "../Shader.h"
#include <tools/vmath.h>

class Shader3dComposer : public Shader {
private:
	Shader3dComposer();
	friend Shader3dComposer *g_Shader3dComposer();

public:
	~Shader3dComposer() override;
	void Render() override;

private:
	GLuint colorUniform;
	GLuint positionUniform;
	GLuint normalUniform;
	GLuint depthUniform;
	GLuint shadowUniform;
	GLuint shadowProjectionMatrixUniform;
};
Shader3dComposer *g_Shader3dComposer();

#endif
