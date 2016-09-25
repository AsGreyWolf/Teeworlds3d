#include "AsyncComponent.h"
#include <shared/Console.h>
AsyncComponent::AsyncComponent(const std::string &tag, long delay) {
	frames = 0;
	t = new DelayedThread([this]() { AsyncTick(); }, delay);
	fps = new DelayedThread(
	    [this, tag]() {
		    g_Console()->Info("[" + tag + "] FPS = " + std::to_string(frames));
		    frames = 0;
		   },
	    1000);
}
AsyncComponent::~AsyncComponent() { Stop(); }
void AsyncComponent::Tick() { SharedComponent::Tick(); }
void AsyncComponent::AsyncTick() { frames++; }
void AsyncComponent::Start() {
	t->Start();
	fps->Start();
}
void AsyncComponent::Stop() {
	t->Stop();
	fps->Stop();
}
