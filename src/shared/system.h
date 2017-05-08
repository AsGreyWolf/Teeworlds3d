#ifndef SYSTEM_H
#define SYSTEM_H

#include "../component.h"

#include <string>
#include <tools/performance.h>
#include <tools/protocol.h>
#include <vector>

namespace tee3d {
namespace shared {
using std::vector;
using std::string;
///<summary>Integraction to OS</summary>
class system_component : public component {
private:
	system_component();

public:
	~system_component() override;
	void tick() override;

	string path() const;
	vector<string> files_in_directory(const string &directory) const;
	string data_file(const string &str) const;
	duration_t time() const;
	template <class T, int FPS> performance_t<FPS> sync(const string &tag) const;
	int fps() const;
	double tick_factor() const;
};
using system = component::wrapper<system_component>;
};
};

#endif
