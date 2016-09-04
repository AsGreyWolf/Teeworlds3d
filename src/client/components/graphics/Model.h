#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <tools/vmath.h>

class Model {
public:
	Model();
	Model(const Model &second);
	virtual ~Model();
	virtual void Render();
	virtual void Enable();
	virtual void Disable();
	inline bool isEnabled() const { return enabled; };

private:
	bool enabled = false;
};

#endif
