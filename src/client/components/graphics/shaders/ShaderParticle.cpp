#include "ShaderParticle.h"

#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/Model.h>
#include <shared/System.h>

#ifndef GL_POINT_SPRITE
#define GL_POINT_SPRITE 0x8861
#endif
#ifndef GL_PROGRAM_POINT_SIZE
#define GL_PROGRAM_POINT_SIZE 0x8642
#endif

ShaderParticle *pShaderParticle;
ShaderParticle *g_ShaderParticle() {
	return pShaderParticle ? pShaderParticle : new ShaderParticle();
}

ShaderParticle::ShaderParticle()
    : Shader::Shader("shaders/shaderParticle", g_Graphics()->screenSize,
                     GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_NONE) {
	pShaderParticle = this;
	perspectiveMatrix = glm::perspective((float)M_PI_2, g_Graphics()->screenAspect,
	                                     1.0f, 10000.0f);
	SetAttribute("in_Position", SHADER_POS);
}
ShaderParticle::~ShaderParticle() { pShaderParticle = 0; }
void ShaderParticle::Render() {
	Shader::Render();
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	SetUniform<int>("time", g_System()->GetTime());
	SetUniform("tex", 0);
	SetUniform("viewProjectionMatrix",
	           perspectiveMatrix * glm::lookAt(g_Camera()->pos,
	                                           g_Camera()->pos + g_Camera()->look,
	                                           g_Camera()->up));

	for (Model *model : registredModels)
		if (model->isEnabled())
			model->Render();

	glDisable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}
void ShaderParticle::SetColor(const glm::vec4 &color) {
	SetUniform("colorer", color);
}
void ShaderParticle::SetMatrix(const glm::mat4 &modelMatrix) {
	SetUniform("modelMatrix", modelMatrix);
}
void ShaderParticle::SetSize(float size) { SetUniform("size", size); }
void ShaderParticle::SetGravity(float gravity) {
	SetUniform("gravity", gravity);
}
void ShaderParticle::SetTTL(float time) { SetUniform("ttl", time); }
void ShaderParticle::SetVel(const glm::vec3 &vel) { SetUniform("vel", vel); }
