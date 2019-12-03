#pragma once
#include "ModulePrototype.h"
#include <string>
#include <map>
#include "Mloader.h"
#include <boost/dll.hpp>
using std::map;
using std::string;
class MShell :
	public ModulePrototype
{
public:
	MShell();
	virtual ~MShell();
	virtual int Module_init(void);
	virtual int Module_exit(void);
	virtual int Module_run(void);
private:
	int pre_install();
	string username;
	Mloader loader;
	map<string, boost::dll::shared_library> instable;
	bool commandExecute(const string& command);
};

