#pragma once
#include "ModulePrototype.h"
#include "sqlite3pp.h"
#include <string>
using std::string;

class Mloader :
	public ModulePrototype
{
public:
	Mloader();
	virtual ~Mloader();
	virtual int Module_init(void);
	virtual int Module_exit(void);
	virtual int Module_run(void);
	int query(const string& command,string& result);
};

