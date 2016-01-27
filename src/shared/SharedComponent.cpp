#include "SharedComponent.h"
#include <list>

std::list <SharedComponent*> SharedComponent::registredSharedComponents;
void SharedComponent::RegisterComponent(SharedComponent* component) {
	registredSharedComponents.push_back(component);
}
void SharedComponent::UnRegisterComponent(SharedComponent* component) {
	registredSharedComponents.remove(component);
}
void SharedComponent::ClearComponents() {
	while (!registredSharedComponents.empty())
		UnRegisterComponent(registredSharedComponents.back());
}
SharedComponent::SharedComponent() {
}
SharedComponent::~SharedComponent() {
}
void SharedComponent::Tick() {
}
void SharedComponent::TickComponents() {
	for (SharedComponent*& component : registredSharedComponents)
		component->Tick();
}