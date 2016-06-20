#ifndef LAYOUT_H
#define LAYOUT_H

#include "View.h"
#include <vector>

class Layout : public View {
public:
	Layout();
	Layout(const Layout &second);
	virtual ~Layout();

	void Show() override;
	void Hide() override;
	virtual void Validate() override;
	void Add(View *view);
	void Remove(View *view);

private:
	std::vector <View*> children;
};

#endif
