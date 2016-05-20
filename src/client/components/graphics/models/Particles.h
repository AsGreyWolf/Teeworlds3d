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
};

#endif
