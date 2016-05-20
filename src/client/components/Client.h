#ifndef CLIENT_H
#define CLIENT_H

#include "../ClientComponent.h"
#include <tools/vmath.h>

class Client : public ClientComponent {
private:
	Client();
	friend Client *g_Client();

public:
	~Client() override;
	void Tick() override;

	void Start();
	void Stop();
	bool isRunning();

private:
	bool working = false;
};
Client *g_Client();

#endif
