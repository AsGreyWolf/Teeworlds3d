#include "Shader3d.h"

#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/Model.h>
#include <client/components/graphics/Texture.h>
#include <string>

Shader3d *pShader3d;
Shader3d *g_Shader3d() { return pShader3d ? pShader3d : new Shader3d(); }

Shader3d::Shader3d()
    : Shader::Shader("shaders/shader3d", g_Graphics()->screenSize, GL_BACK,
                     GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
	pShader3d = this;
	perspectiveMatrix = glm::perspective((float)M_PI_2, g_Graphics()->screenAspect,
	                                     1.0f, 10000.0f);
	SetAttribute("in_Position", SHADER_POS);
	SetAttribute("in_TexMap", SHADER_TEXMAP);
	SetAttribute("in_Normal", SHADER_NORMAL);

	AddOutputTexture(color = Texture(nullptr, viewport));
	AddOutputTexture(
	    position = Texture(nullptr, viewport, TEXTURE_FLOAT | TEXTURE_3CORD));
	AddOutputTexture(
	    normal = Texture(nullptr, viewport, TEXTURE_FLOAT | TEXTURE_3CORD));
	AddOutputTexture(depth = Texture(nullptr, viewport, TEXTURE_DEPTH));
}
Shader3d::~Shader3d() { pShader3d = nullptr; }
void Shader3d::Render() {
	Shader::Render();
	static Uniform<int> texture(*this, "tex");
	texture.Set(0);
	static Uniform<glm::mat4> vpMatrix(*this, "viewProjectionMatrix");
	vpMatrix.Set(perspectiveMatrix *
	             glm::lookAt(g_Camera()->pos, g_Camera()->pos + g_Camera()->look,
	                         g_Camera()->up));

	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();
}
void Shader3d::SetLight(const bool light) {
	static Uniform<float> lighting(*this, "lighting");
	lighting.Set(light ? 1.0f : 0.0f);
}
void Shader3d::SetColor(const glm::vec4 &color) {
	static Uniform<glm::vec4> colorer(*this, "colorer");
	colorer.Set(color);
}
void Shader3d::SetMatrix(const glm::mat4 &modelMatrix,
                         const glm::mat4 &normalMatrix) {
	static Uniform<glm::mat4> nMatrix(*this, "normalMatrix");
	nMatrix.Set(normalMatrix);
	static Uniform<glm::mat4> mMatrix(*this, "modelMatrix");
	mMatrix.Set(modelMatrix);
}
