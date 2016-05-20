#ifndef SYSTEM_H
#define SYSTEM_H

#include "SharedComponent.h"

#include <string>
#include <vector>

///<summary>Interaction with OS</summary>
class System : public SharedComponent {
private:
	System();
	friend System *g_System();

public:
	~System() override;

	///<summary>Tick the component(graphics thread)</summary>
	void Tick() override;

	///<summary>Returns app directory path</summary>
	std::string GetPath() const;
	///<summary>Returns time in ms</summary>
	long GetTime() const;
	///<summary>Fills out with filenames in the directory</summary>
	void GetFilesInDirectory(std::vector<std::string> &out,
	                         const std::string &directory) const;
	///<summary>Returns filename in data folder</summary>
	///<param name="str">Filename</param>
	std::string GetDataFile(const std::string &str) const;

	int fps;
	double tickCoeff;

private:
	std::string PATH_CUR;
	std::string PATH_DATA;
	long lasttickTime;
};
System *g_System();

#endif
