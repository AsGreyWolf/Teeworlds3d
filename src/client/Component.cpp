#include "Component.h"

std::list <Component*> Component::registredComponents;
void Component::RegisterComponent(Component* component) {
	SharedComponent::RegisterComponent((SharedComponent*)component);
	registredComponents.push_back(component);
}
void Component::UnRegisterComponent(Component* component) {
	registredComponents.remove(component);
	SharedComponent::UnRegisterComponent((SharedComponent*)component);
	delete component;
}
void Component::ClearComponents() {
	while (!registredComponents.empty())
		UnRegisterComponent(registredComponents.back());
}
Component::Component():SharedComponent() {
}
Component::~Component() {
}
void Component::Input(unsigned char* keys, int xrel, int yrel, int wheel) {
}
void Component::Message(int type, char* value) {
}
void Component::StateChange(const STATE& lastState) {
}
void Component::InputComponents(unsigned char* keys, int xrel, int yrel, int wheel) {
	for (Component*& component : registredComponents)
		component->Input(keys, xrel, yrel, wheel);
}
void Component::MessageComponents(int type, char* value) {
	for (Component*& component : registredComponents)
		component->Message(type,value);
}
void Component::StateChangeComponents(const STATE& lastState) {
	for (Component*& component : registredComponents)
		component->StateChange(lastState);
}