#ifndef UI_H
#define UI_H

#include "../ClientComponent.h"
#include <client/components/ui/Layout.h>
#include <set>

class View;

class UI : public ClientComponent {
private:
	UI();
	friend UI *g_UI();

public:
	~UI() override;
	void Tick() override;

	void RegisterView(View *view);
	void UnregisterView(View *view);

	Layout *screenLayout;

private:
	std::set<View *> registredViews;
};
UI *g_UI();

#endif
