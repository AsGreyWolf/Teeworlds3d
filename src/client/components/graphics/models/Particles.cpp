#include "Particles.h"

#include <client/components/graphics/geometry/Primitives.h>
#include <client/components/graphics/shaders/Shader3d.h>
#include <client/components/graphics/shaders/ShaderParticle.h>

Particles::Particles() : Model3d(false, GL_POINTS) {
	g_Shader3d()->UnregisterModel(this);
	g_ShaderParticle()->RegisterModel(this);
}
Particles::Particles(const Particles &second) : Model3d(second) {
	g_Shader3d()->UnregisterModel(this);
	g_ShaderParticle()->RegisterModel(this);
	Particles::operator=(second);
}
Particles &Particles::operator=(const Particles &second) {
	Model3d::operator=(second);
	particleSize = second.particleSize;
	particleCount = second.particleCount;
	particleGravity = second.particleGravity;
	particleTtl = second.particleTtl;
	particleVel = second.particleVel;
	return *this;
}
Particles::~Particles() { g_ShaderParticle()->UnregisterModel(this); }
void Particles::Render() {
	texture.Bind();
	g_ShaderParticle()->SetSize(particleSize);
	g_ShaderParticle()->SetGravity(particleGravity);
	g_ShaderParticle()->SetTTL(particleTtl);
	g_ShaderParticle()->SetVel(particleVel);
	g_ShaderParticle()->SetColor(color);
	g_ShaderParticle()->SetMatrix(modelMatrix);
	data->Render(type);
}
void Particles::Add(int c) {
	for (int i = 0; i < c; i++) {
		particleCount++;
		Model3d::Add(Point(glm::vec3(particleCount, particleCount * particleCount, particleCount * particleCount * particleCount)));
	}
}
