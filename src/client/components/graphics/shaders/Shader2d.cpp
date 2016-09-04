#include "Shader2d.h"

#include <client/components/Graphics.h>
#include <client/components/graphics/Model.h>
#include <string>

Shader2d *pShader2d;
Shader2d *g_Shader2d() { return pShader2d ? pShader2d : new Shader2d(); }

Shader2d::Shader2d()
    : Shader::Shader("shaders/shader2d", g_Graphics()->screenSize, GL_BACK,
                     GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_DEPTH_BUFFER_BIT) {
	pShader2d = this;
	SetAttribute("in_Position", SHADER_POS);
	SetAttribute("in_TexMap", SHADER_TEXMAP);
}
Shader2d::~Shader2d() { pShader2d = 0; }
void Shader2d::Render() {
	Shader::Render();
	static Uniform<int> texture(*this, "tex");
	texture.Set(0);
	static Uniform<float> aspect(*this, "aspect");
	aspect.Set(g_Graphics()->screenAspect);

	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();
}
void Shader2d::SetColor(const glm::vec4 &color) {
	static Uniform<glm::vec4> colorer(*this, "colorer");
	colorer.Set(color);
}
void Shader2d::SetPosition(const glm::vec2 &pos, float depth) {
	static Uniform<glm::vec3> position(*this, "pos");
	position.Set(glm::vec3(pos, depth));
}
