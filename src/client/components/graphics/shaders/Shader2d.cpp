#include "Shader2d.h"

#include "../../Graphics.h"
#include "../Model.h"
#include <string>

Shader2d *pShader2d;
Shader2d *g_Shader2d() { return pShader2d ? pShader2d : new Shader2d(); }

Shader2d::Shader2d()
    : Shader::Shader(std::string("shaders/shader2d"), g_Graphics()->screenSize,
                     GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_DEPTH_BUFFER_BIT) {
	pShader2d = this;

	GLuint id = *pShader2d;

	glBindAttribLocation(id, SHADER_POS, "in_Position");
	glBindAttribLocation(id, SHADER_TEXMAP, "in_TexMap");

	colorUniform = glGetUniformLocation(id, "colorer");
	aspectUniform = glGetUniformLocation(id, "aspect");
	positionUniform = glGetUniformLocation(id, "pos");
	textureUniform = glGetUniformLocation(id, "tex");
}
Shader2d::~Shader2d() { pShader2d = 0; }
void Shader2d::Render() {
	Shader::Render();
	glUniform1i(textureUniform, 0);
	glUniform1f(aspectUniform, g_Graphics()->screenAspect);

	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();
}
void Shader2d::SetColor(const glm::vec4 &color) {
	glUniform4f(colorUniform, color.r, color.g, color.b, color.a);
}
void Shader2d::SetPosition(const glm::vec2 &pos, float depth) {
	glUniform3f(positionUniform, pos.x, pos.y, depth);
}
