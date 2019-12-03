#include "pch.h"
#include "Mloader.h"
#include <iostream>
using std::cout;
using std::endl;
Mloader::Mloader()
{
	Module_init();
}


Mloader::~Mloader()
{
	Module_exit();
}

int Mloader::Module_init(void)
{
	return 1;
}
int Mloader::Module_exit(void)
{
	return 1;
}
int Mloader::Module_run(void)
{
	return 1;
}

int Mloader::query(const string& command,string& result)
{
	result = "";
	try {
		sqlite3pp::database db("module.db");
		sqlite3pp::query qry(db, "SELECT modname, modpath FROM modRegisterTbl ");
		for (auto v : qry) {
			string name, path;
			v.getter() >> name>>path;
			if (name == command)
				result = path;
		}
	}
	catch (std::exception& ex)
	{
		cout << ex.what()<<endl;
	}
	return 1;
}


