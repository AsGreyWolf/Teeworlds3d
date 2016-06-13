#ifndef PARTICLES_H
#define PARTICLES_H

#include "Model3d.h"

class Particles : public Model3d {
public:
	Particles();
	Particles(const Particles &second);
	virtual ~Particles() override;
	virtual void Render() override;

	Particles &operator=(const Particles &second);

	void Add(int count = 1);

	float particleSize = 1.0f;
	float particleGravity = 0.0f;
	float particleTtl = 1000.0f;
	glm::vec3 particleVel = glm::vec3(0, 0, 0);

protected:
	void Add(const Geometry3d &geom);
	int particleCount = 0;
};

#endif
