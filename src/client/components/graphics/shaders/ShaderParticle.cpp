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
	return pShaderParticle != nullptr ? pShaderParticle : new ShaderParticle();
}

ShaderParticle::ShaderParticle()
    : Shader::Shader("shaders/shaderParticle", g_Graphics()->screenSize,
                     GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_NONE) {
	pShaderParticle = this;
	perspectiveMatrix = glm::perspective(
	    static_cast<float>(M_PI_2), g_Graphics()->screenAspect, 1.0f, 10000.0f);
	SetAttribute("in_Position", SHADER_POS);
}
ShaderParticle::~ShaderParticle() { pShaderParticle = nullptr; }
void ShaderParticle::Render() {
	Shader::Render();
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	static Uniform<int> time(*this, "time");
	time.Set(g_System()->GetTime());
	static Uniform<int> texture(*this, "tex");
	texture.Set(0);
	static Uniform<glm::mat4> vpMatrix(*this, "viewProjectionMatrix");
	vpMatrix.Set(perspectiveMatrix *
	             glm::lookAt(g_Camera()->pos, g_Camera()->pos + g_Camera()->look,
	                         g_Camera()->up));

	for (Model *model : registredModels) {
		if (model->isEnabled()) {
			model->Render();
		}
	}

	glDisable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}
void ShaderParticle::SetColor(const glm::vec4 &color) {
	static Uniform<glm::vec4> colorer(*this, "colorer");
	colorer.Set(color);
}
void ShaderParticle::SetMatrix(const glm::mat4 &modelMatrix) {
	static Uniform<glm::mat4> mMatrix(*this, "modelMatrix");
	mMatrix.Set(modelMatrix);
}
void ShaderParticle::SetSize(float s) {
	static Uniform<float> size(*this, "size");
	size.Set(s);
}
void ShaderParticle::SetGravity(float g) {
	static Uniform<float> gravity(*this, "gravity");
	gravity.Set(g);
}
void ShaderParticle::SetTTL(float t) {
	static Uniform<float> ttl(*this, "ttl");
	ttl.Set(t);
}
void ShaderParticle::SetVel(const glm::vec3 &v) {
	static Uniform<glm::vec3> vel(*this, "vel");
	vel.Set(v);
}
