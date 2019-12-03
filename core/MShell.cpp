#include "pch.h"
#include "MShell.h"
#include <string>
#include <iostream>
#include <boost/dll.hpp>
#include <utility>
using std::string;
using std::cout;
using std::cin;
using std::endl;
MShell::MShell():username("")
{
	Module_init();
}

MShell::~MShell()
{
	Module_exit();
}

int MShell::Module_init(void)
{
	cout << "请输入用户名:";
	cin >> username;
	pre_install();  //将注册在数据库中的模块同一安装到instable中
	for (auto item : instable)
	{
		auto f = item.second.get<ModulePrototype*(void)>("GetInstance");
		auto p = f();
		p->Module_init();
	}
	return 1;
}

int MShell::Module_run(void)
{
	string command_buffer;
	bool flag = 1;
	while (1)
	{
		if (!flag)
			break;
		cout << username<<":";
		cin >> command_buffer;
		flag = commandExecute(command_buffer);
		command_buffer = "";
	}
	return 1;
}

int MShell::Module_exit(void)
{
	int tmp;
	cout << "Mshell closed"<<endl<<"please push any key to leave";
	cin >> tmp;
	return 1;
}

bool MShell::commandExecute(const string& command)
{
	auto m_iter = instable.find(command);
	if (m_iter != instable.end())
	{
		auto f = (*m_iter).second.get<ModulePrototype*(void)>("GetInstance");
		auto tmp = f();
		tmp->Module_run();
	}
	else {
		string result;
		loader.query(command, result);
		if (result != "")
		{
			boost::dll::shared_library lib(result.c_str());
			std::pair<string, boost::dll::shared_library> tmp;
			tmp.first = command;
			tmp.second = lib;
			instable.insert(tmp);
			auto f = lib.get<ModulePrototype*(void)>("GetInstance");
			auto t = f();
			t->Module_init();
			t->Module_run();
		}
		else {
			cout << "no such command ,please regisiter"<<endl;
		}
	}
	
	return 1;

}

int MShell::pre_install()
{
	std::pair<string, boost::dll::shared_library> tmp;
	try {
		sqlite3pp::database db("module.db");
		sqlite3pp::query qry(db, "SELECT modname, modpath FROM modRegisterTbl ");
		for (auto v : qry) {
			string name, path;
			v.getter() >> name >> path;
			tmp.first = name;
			boost::dll::shared_library lib(path.c_str());
			tmp.second = lib;
			instable.insert(tmp);
		}
	}
	catch (std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 1;
}