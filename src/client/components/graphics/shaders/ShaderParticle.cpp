#include "ShaderParticle.h"

#include <shared/System.h>
#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/Model.h>

ShaderParticle *pShaderParticle;
ShaderParticle *g_ShaderParticle() {
	return pShaderParticle ? pShaderParticle : new ShaderParticle();
}

ShaderParticle::ShaderParticle()
    : Shader::Shader(std::string("shaders/shaderParticle"),
                     g_Graphics()->screenSize, GL_BACK, GL_TRUE, GL_TRUE,
                     GL_TRUE, GL_TRUE, GL_TRUE, GL_NONE) {
	pShaderParticle = this;
	perspectiveMatrix = glm::perspective((float)M_PI_2, g_Graphics()->screenAspect,
	                                     1.0f, 10000.0f);

	GLuint id = *pShaderParticle;

	glBindAttribLocation(id, SHADER_POS, "in_Position");

	colorUniform = glGetUniformLocation(id, "colorer");
	viewProjectionMatrixUniform = glGetUniformLocation(id, "viewProjectionMatrix");
	modelMatrixUniform = glGetUniformLocation(id, "modelMatrix");
	textureUniform = glGetUniformLocation(id, "tex");
	timeUniform = glGetUniformLocation(id, "time");
	sizeUniform = glGetUniformLocation(id, "size");
	gravityUniform = glGetUniformLocation(id, "gravity");
	ttlUniform = glGetUniformLocation(id, "ttl");
	velUniform = glGetUniformLocation(id, "vel");
}
ShaderParticle::~ShaderParticle() { pShaderParticle = 0; }
void ShaderParticle::Render() {
	Shader::Render();
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUniform1i(timeUniform, g_System()->GetTime());
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

	glDisable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}
void ShaderParticle::SetColor(const glm::vec4 &color) {
	glUniform4f(colorUniform, color.r, color.g, color.b, color.a);
}
void ShaderParticle::SetMatrix(const glm::mat4 &modelMatrix) {
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(modelMatrix));
}
void ShaderParticle::SetSize(float size) { glUniform1f(sizeUniform, size); }
void ShaderParticle::SetGravity(float gravity) {
	glUniform1f(gravityUniform, gravity);
}
void ShaderParticle::SetTTL(float time) { glUniform1f(ttlUniform, time); }
void ShaderParticle::SetVel(const glm::vec3 &vel) {
	glUniform3f(velUniform, vel.x, vel.y, vel.z);
}
