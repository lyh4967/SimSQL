#include <iostream>
#include <string>
#include "SubFunc.h"
#include "Table.h"
using namespace std;

enum DML{INSERT,DELETE,UPDATE,SELECT};
QueType<string> StringSplit(string strTarget, string strTok); //string.split
void SQLProcessor(string s,Table& table);

//���̺��̸����� output���� ��������
ofstream output("data.bin", ios::out | ios::binary);
int main(){

	
	//ifstream input("data.bin", ios::in | ios::binary);
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
	/*vector<string> tokens;
	istringstream iss(s);
	copy(istream_iterator<string>(iss),
	istream_iterator<string>(),
	back_inserter<vector<string> >(tokens));*/

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
