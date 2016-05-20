#include "Shader3d.h"

#include "../../Camera.h"
#include "../../Graphics.h"
#include "../Texture.h"
#include "../Model.h"
#include "ShaderShadow.h"
#include <string>

Shader3d *pShader3d;
Shader3d *g_Shader3d() { return pShader3d ? pShader3d : new Shader3d(); }

Shader3d::Shader3d()
    : Shader::Shader(std::string("shaders/shader3d"), g_Graphics()->screenSize,
                     GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
	pShader3d = this;
	perspectiveMatrix = glm::perspective((float)M_PI_2, g_Graphics()->screenAspect,
	                                     1.0f, 10000.0f);

	GLuint id = *pShader3d;

	glBindAttribLocation(id, SHADER_POS, "in_Position");
	glBindAttribLocation(id, SHADER_TEXMAP, "in_TexMap");
	glBindAttribLocation(id, SHADER_NORMAL, "in_Normal");

	colorUniform = glGetUniformLocation(id, "colorer");
	lightUniform = glGetUniformLocation(id, "lighting");
	viewProjectionMatrixUniform = glGetUniformLocation(id, "viewProjectionMatrix");
	modelMatrixUniform = glGetUniformLocation(id, "modelMatrix");
	normalMatrixUniform = glGetUniformLocation(id, "normalMatrix");
	shadowProjectionMatrixUniform =
	    glGetUniformLocation(id, "shadowProjectionMatrix");
	textureUniform = glGetUniformLocation(id, "tex");
	shadowUniform = glGetUniformLocation(id, "shadow");
}
Shader3d::~Shader3d() { pShader3d = 0; }
void Shader3d::Render() {
	Shader::Render();
	glUniform1i(textureUniform, 0);
	glUniform1i(shadowUniform, 1);
	glUniformMatrix4fv(
	    viewProjectionMatrixUniform, 1, GL_FALSE,
	    (const float *)glm::value_ptr(
	        perspectiveMatrix * glm::lookAt(g_Camera()->pos,
	                                        g_Camera()->pos + g_Camera()->look,
	                                        g_Camera()->up)));
	glUniformMatrix4fv(shadowProjectionMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(g_ShaderShadow()->matrix));
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	g_ShaderShadow()->texture.Bind();
	glActiveTexture(GL_TEXTURE0);

	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
}
void Shader3d::SetLight(const bool light) {
	glUniform1f(lightUniform, light ? 1.0f : 0.0f);
}
void Shader3d::SetColor(const glm::vec4 &color) {
	glUniform4f(colorUniform, color.r, color.g, color.b, color.a);
}
void Shader3d::SetMatrix(const glm::mat4 &modelMatrix,
                         const glm::mat4 &normalMatrix) {
	glUniformMatrix4fv(normalMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(modelMatrix));
}
