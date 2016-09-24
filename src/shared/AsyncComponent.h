#ifndef ASYNCCOMPONENT_H
#define ASYNCCOMPONENT_H

#include "SharedComponent.h"
#include <shared/System.h>

class AsyncComponent : public SharedComponent {
protected:
	AsyncComponent(long delay);
	void Start();
	void Stop();

public:
	virtual void Tick() override final;
	virtual ~AsyncComponent() override;
	virtual void AsyncTick();

private:
	class DelayedThread *t;
	class DelayedThread *fps;
	long frames;
};

#endif
