#include "Shader3d.h"

#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/Model.h>
#include <client/components/graphics/Texture.h>
#include <string>

Shader3d *pShader3d;
Shader3d *g_Shader3d() { return pShader3d ? pShader3d : new Shader3d(); }

unsigned static int bufferList[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
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
	textureUniform = glGetUniformLocation(id, "tex");
	depth=Texture(NULL, viewport.x, viewport.y,
						  TEXTURE_DEPTH);
	color=Texture(NULL, viewport.x, viewport.y,
						  0);
	position=Texture(NULL, viewport.x, viewport.y,
						  TEXTURE_FLOAT);
	normal=Texture(NULL, viewport.x, viewport.y,
						  TEXTURE_FLOAT);
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDrawBuffers(3, bufferList);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
							  GL_TEXTURE_2D, color, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
							  GL_TEXTURE_2D, position, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
							  GL_TEXTURE_2D, normal, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
							  GL_TEXTURE_2D, depth, 0);
}
Shader3d::~Shader3d() {
	glDeleteFramebuffers(1, &framebuffer);
	pShader3d = 0;
}
void Shader3d::Render() {
	Shader::Render();
	glUniform1i(textureUniform, 0);
	glUniformMatrix4fv(
	    viewProjectionMatrixUniform, 1, GL_FALSE,
	    (const float *)glm::value_ptr(
	        perspectiveMatrix * glm::lookAt(g_Camera()->pos,
	                                        g_Camera()->pos + g_Camera()->look,
	                                        g_Camera()->up)));

	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();
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
