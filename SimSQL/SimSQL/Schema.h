#pragma once
#include "myLib.h"
#include "Table.h"
class Schema
{
private:
	string schema_name;
	map<string, Table> schema_list;
public:
	Schema();//constructor
	~Schema();//destructor
	void Create_tbl();
	void Drop_tbl();
	void Alter_tbl();
};

