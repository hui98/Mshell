#pragma once
class ModulePrototype
{
public:
	ModulePrototype();
	virtual ~ModulePrototype();
	virtual int Module_init(void) = 0;
	virtual int Module_exit(void) = 0;
	virtual int Module_run(void) = 0;
};

