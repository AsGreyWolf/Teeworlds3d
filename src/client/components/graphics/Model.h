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
	inline bool isEnabled() { return enabled; };

private:
	bool enabled = false;
};

typedef std::shared_ptr<Model> ModelPtr;
#define ModelPtr(a) std::make_shared<Model>(a);

#endif
