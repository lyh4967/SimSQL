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

	QueType<string> commandQ(StringSplit(s, " "));//공백을 기준으로 구문 분리

	commandQ.Dequeue(command);

	if (command == "INSERT") {//INSERT시에

		commandQ.Dequeue(command);
		QueType<string> subQ(StringSplit(command, ","));//넘길 값들 subQ큐에 넣기

		table.Insert(subQ);
	}
	else if (command == "SELECT") {//SELECT시에
		table.Select(commandQ);
	}
	else if (command == "COMMIT") {//COMMIT시에
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