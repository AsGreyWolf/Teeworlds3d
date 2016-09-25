#include "SharedComponent.h"

#include <list>

std::list<SharedComponent *> SharedComponent::registred;

SharedComponent::SharedComponent() { registred.push_back(this); }
SharedComponent::~SharedComponent() { registred.remove(this); }
void SharedComponent::Tick() {}
void SharedComponent::ClearComponents() {
	while (!registred.empty()) {
		delete registred.back();
	}
}
void SharedComponent::TickComponents() {
	for (SharedComponent *&component : registred) {
		component->Tick();
	}
}
