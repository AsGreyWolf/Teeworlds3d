#include "Particles.h"

#include <client/components/graphics/shaders/Shader3d.h>
#include <client/components/graphics/shaders/ShaderParticle.h>

Particles::Particles() : Model3d(false, GL_POINTS) {
	g_Shader3d()->UnregisterModel(this);
	g_ShaderParticle()->RegisterModel(this);
}
Particles::Particles(const Particles &second) : Model3d(second) {
	g_Shader3d()->UnregisterModel(this);
	g_ShaderParticle()->RegisterModel(this);
}
Particles &Particles::operator=(const Particles &second) {
	Model3d::operator=(second);
	return *this;
}
Particles::~Particles() { g_ShaderParticle()->UnregisterModel(this); }
void Particles::Render() {
	glPointSize(glm::length(scale));
	texture.Bind();
	g_ShaderParticle()->SetColor(color);
	g_ShaderParticle()->SetMatrix(modelMatrix);
	data->Render(type);
}
