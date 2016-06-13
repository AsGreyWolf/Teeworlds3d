#include "ShaderShadow.h"

#include <client/components/Graphics.h>
#include <client/components/Camera.h>
#include <client/components/graphics/Model.h>

ShaderShadow *pShaderShadow;
ShaderShadow *g_ShaderShadow() {
	return pShaderShadow ? pShaderShadow : new ShaderShadow();
}

ShaderShadow::ShaderShadow()
    : Shader::Shader(
          std::string("shaders/shaderShadow"),
          glm::vec2(g_Graphics()->screenSize.x, g_Graphics()->screenSize.x),
          GL_FRONT, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE,
          GL_DEPTH_BUFFER_BIT) {
	pShaderShadow = this;
	texture = Texture(NULL, g_Graphics()->screenSize.x, g_Graphics()->screenSize.x,
	                  TEXTURE_ANISOTROPY | TEXTURE_FILTERING | TEXTURE_DEPTH);

	orthoMatrix = glm::ortho(-320.0f, 320.0f, -320.0f, 320.0f, -1000.0f, 0.0f);

	GLuint id = *pShaderShadow;

	glBindAttribLocation(id, SHADER_POS, "in_Position");
	glBindAttribLocation(id, SHADER_TEXMAP, "in_TexMap");

	viewProjectionMatrixUniform = glGetUniformLocation(id, "viewProjectionMatrix");
	modelMatrixUniform = glGetUniformLocation(id, "modelMatrix");
	textureUniform = glGetUniformLocation(id, "tex");

	glGenFramebuffersEXT(1, &framebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
	                          GL_TEXTURE_2D, texture, 0);
}
ShaderShadow::~ShaderShadow() {
	glDeleteFramebuffers(1, &framebuffer);
	pShaderShadow = 0;
}
void ShaderShadow::Render() {
	Shader::Render();
	glUniform1i(textureUniform, 0);
	glm::vec3 pos = g_Camera()->pos;
	pos.z = 0;
	matrix = orthoMatrix *
	         glm::lookAt(pos, pos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(viewProjectionMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(matrix));
	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();
}
void ShaderShadow::SetMatrix(const glm::mat4 &modelMatrix) {
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(modelMatrix));
}
