#include "SubFunc.h"
#include "Table.h"
#include "myLib.h"
using namespace std;

void SQLProcessor(string s,Table& table);

int main(){

	ifstream commandInput("commandSQL.txt");
	Table table("test",3,"�й�","�̸�","�б�");//���̺�(���̺��̸�, �ʵ����,�ʵ��)
	cout << "Hello customer, This is SimSQL" << endl;
	bool flag = true;
	string sql;
	while (flag){
		cout << ">";
		getline(commandInput, sql);//SQL�Է¹ޱ�
		cout << sql << endl;
		SQLProcessor(sql,table);//SQLó���� (sql,���̺�)
		if (sql == "q")
			flag = false;

	}
	return 0;
}
void SQLProcessor(string s, Table& table){

	QueType<string> commandQ(StringSplit(s, " "));//������ �������� ���� �и�
	string command;
	commandQ.Dequeue(command);
	
	if (command == "INSERT"){//INSERT�ÿ�

		commandQ.Dequeue(command);
		QueType<string> subQ(StringSplit(command, ","));//�ѱ� ���� subQť�� �ֱ�
		
		table.Insert(subQ);
	}
	else if (command == "SELECT"){//SELECT�ÿ�
		table.Select(commandQ);
	}
	else if (command == "COMMIT") {//COMMIT�ÿ�
		table.Commit();
	}
	else if (command == "READ") {
		table.Read();
	}
}
