#include "ClientComponent.h"

std::list<ClientComponent *> ClientComponent::registred;
STATE ClientComponent::state;

ClientComponent::ClientComponent() : SharedComponent() {
	registred.push_back(this);
}
ClientComponent::~ClientComponent() { registred.remove(this); }
void ClientComponent::Message(int type, char *value) {}
void ClientComponent::StateChange(const STATE &prevState) {}
void ClientComponent::ClearComponents() {
	while (!registred.empty())
		delete registred.back();
	SharedComponent::ClearComponents();
}
void ClientComponent::MessageComponents(int type, char *value) {
	for (ClientComponent *&component : registred)
		component->Message(type, value);
}
void ClientComponent::StateChangeComponents(const STATE &prevState) {
	for (ClientComponent *&component : registred)
		component->StateChange(prevState);
}
