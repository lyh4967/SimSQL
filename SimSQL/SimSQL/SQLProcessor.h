#pragma once
#include "myLib.h"
#include "SubFunc.h"
#include "Table.h"
class SQLProcessor
{
private:

public:
	SQLProcessor();
	~SQLProcessor();
	void Process(string s, Table& table);
};

