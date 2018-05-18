#include "SQLProcessor.h"



SQLProcessor::SQLProcessor()
{
}


SQLProcessor::~SQLProcessor()
{
}
void SQLProcessor::Process(string s, Table& table) {
	string command;

	command = s.substr(0, s.find(" "));
	cout << "log:" << command << endl;

	QueType<string> commandQ(StringSplit(s, " "));//������ �������� ���� �и�

	commandQ.Dequeue(command);

	if (command == "INSERT") {//INSERT�ÿ�

		commandQ.Dequeue(command);
		QueType<string> subQ(StringSplit(command, ","));//�ѱ� ���� subQť�� �ֱ�

		table.Insert(subQ);
	}
	else if (command == "SELECT") {//SELECT�ÿ�
		table.Select(commandQ);
	}
	else if (command == "COMMIT") {//COMMIT�ÿ�
		table.Commit();
	}
	else if (command == "READ") {
		table.Read();
	}
	else if (command == "CREATE") {
		commandQ.Dequeue(command);
		//schema.Create_tbl();

	}
}