#ifndef LOADING_H
#define LOADING_H

#include "../ClientComponent.h"
#include <client/components/ui/Panel.h>
#include <functional>
#include <queue>

class Loading : public ClientComponent {
private:
	Loading();
	friend Loading *g_Loading();

public:
	~Loading() override;
	void Tick() override;

	void Push(const std::function<void()> &f);

private:
	std::queue<std::function<void()>> queue;
	Panel status;
	size_t processed = 0;
};
Loading *g_Loading();

#endif
