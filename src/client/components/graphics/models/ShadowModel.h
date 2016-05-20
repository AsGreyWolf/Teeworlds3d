#ifndef SHADOWMODEL_H
#define SHADOWMODEL_H

#include "Model3d.h"

class Model3d::ShadowModel : public Model {
public:
	ShadowModel(Model3d &parent);
	~ShadowModel() override;
	void Render() override;

private:
	Model3d *parent;
};

#endif
