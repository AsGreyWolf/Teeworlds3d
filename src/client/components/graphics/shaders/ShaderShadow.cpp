#include "ShaderShadow.h"

#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/Model.h>

ShaderShadow *pShaderShadow;
ShaderShadow *g_ShaderShadow() {
	return pShaderShadow ? pShaderShadow : new ShaderShadow();
}

ShaderShadow::ShaderShadow()
    : Shader::Shader(
          "shaders/shaderShadow",
          glm::vec2(g_Graphics()->screenSize.x, g_Graphics()->screenSize.x),
          GL_FRONT, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE,
          GL_DEPTH_BUFFER_BIT) {
	pShaderShadow = this;
	orthoMatrix = glm::ortho(-320.0f, 320.0f, -320.0f, 320.0f, -1000.0f, 0.0f);
	SetAttribute("in_Position", SHADER_POS);
	SetAttribute("in_TexMap", SHADER_TEXMAP);

	AddOutputTexture(shadowMap = Texture(NULL, viewport, TEXTURE_ANISOTROPY |
	                                                         TEXTURE_FILTERING |
	                                                         TEXTURE_DEPTH));
}
ShaderShadow::~ShaderShadow() { pShaderShadow = 0; }
void ShaderShadow::Render() {
	Shader::Render();
	static Uniform<int> texture(*this, "tex");
	texture.Set(0);
	glm::vec3 pos = g_Camera()->pos;
	pos.z = 0;
	matrix = orthoMatrix *
	         glm::lookAt(pos, pos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	static Uniform<glm::mat4> vpMatrix(*this, "viewProjectionMatrix");
	vpMatrix.Set(matrix);
	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();
}
void ShaderShadow::SetMatrix(const glm::mat4 &modelMatrix) {
	static Uniform<glm::mat4> mMatrix(*this, "modelMatrix");
	mMatrix.Set(modelMatrix);
}
