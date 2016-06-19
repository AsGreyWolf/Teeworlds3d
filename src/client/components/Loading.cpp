#include "Loading.h"
#include <shared/System.h>
#include <client/components/Graphics.h>
#include <client/components/Resources.h>
#include <client/components/graphics/geometry/Primitives.h>

class Loading *pLoading;
Loading *g_Loading() { return pLoading ? pLoading : new Loading(); }

Loading::Loading() : ClientComponent() {
	pLoading = this;
	status.Add(Quad(g_Graphics()->screen));
	status.texture = g_Resources()->textureBlank;
}
Loading::~Loading() { pLoading = 0; }
void Loading::Tick() {
	if(!queue.empty() && !status.isEnabled()){
		processed = 0;
		status.Enable();
	}
	else if(!queue.empty()){
		float statusValue = processed * 1.0f / (processed + queue.size());
		status.color.a = 1.0f - statusValue;
		long start = g_System()->GetTime();
		while(!queue.empty() && g_System()->GetTime()-start < 1000 / 60){
			queue.front()();
			queue.pop();
			processed++;
		}
	}
	else
		status.Disable();
}
void Loading::Push(const std::function<void ()> &f) {
	queue.push(f);
}
