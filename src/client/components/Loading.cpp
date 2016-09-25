#include "Loading.h"
#include <client/components/Resources.h>
#include <client/components/UI.h>
#include <client/components/ui/Layout.h>
#include <shared/System.h>

class Loading *pLoading;
Loading *g_Loading() { return pLoading != nullptr ? pLoading : new Loading(); }

Loading::Loading() : ClientComponent() {
	pLoading = this;
	g_UI()->screenLayout->Add(&status);
	status.Hide();
}
Loading::~Loading() {
	pLoading = nullptr;
	g_UI()->screenLayout->Remove(&status);
}
void Loading::Tick() {
	if (!queue.empty() && !status.isVisible()) {
		processed = 0;
		status.Show();
	} else if (!queue.empty()) {
		float statusValue = processed * 1.0f / (processed + queue.size());
		status.color.a = 1.0f - statusValue;
		long start = g_System()->GetTime();
		while (!queue.empty() && g_System()->GetTime() - start < 1000 / 60) {
			queue.front()();
			queue.pop();
			processed++;
		}
	} else {
		status.Hide();
	}
}
void Loading::Push(const std::function<void()> &f) { queue.push(f); }
