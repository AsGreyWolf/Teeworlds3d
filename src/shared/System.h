#ifndef SYSTEM_H
#define SYSTEM_H

#include "SharedComponent.h"
#include <string>
#include <vector>

///<summary>Interaction with OS</summary>
class System : public SharedComponent{
public:
	System();
	~System();

	///<summary>Tick the component</summary>
	void Tick();

	///<summary>Returns app directory path</summary>
	string GetPath();
	///<summary>Returns time in ms</summary>
	long GetTime();
	///<summary>Fills out with filenames in the directory</summary>
	void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory);
	///<summary>Returns filename in data folder</summary>
	///<param name="str">Filename</param>
	string System::GetDataFile(string str);

	static const int MAX_FILENAME;
private:
	string PATH_CUR;
	string PATH_DATA;
};
System* g_System();

#endif