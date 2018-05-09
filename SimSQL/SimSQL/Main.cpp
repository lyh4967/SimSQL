#include <iostream>
#include <string>
#include "SubFunc.h"
#include "Table.h"
using namespace std;

enum DML{INSERT,DELETE,UPDATE,SELECT};
QueType<string> StringSplit(string strTarget, string strTok); //string.split
void SQLProcessor(string s,Table& table);

//테이블이름으로 output파일 생성하자
ofstream output("data.bin", ios::out | ios::binary);
int main(){

	
	//ifstream input("data.bin", ios::in | ios::binary);
	ifstream commandInput("commandSQL.txt");
	Table table("test",3,"학번","이름","학교");//테이블(테이블이름, 필드길이,필드명)
	cout << "Hello customer, This is SimSQL" << endl;
	bool flag = true;
	string sql;
	while (flag){
		cout << ">";
		getline(commandInput, sql);//SQL입력받기
		cout << sql << endl;
		SQLProcessor(sql,table);//SQL처리기 (sql,테이블)
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

	QueType<string> commandQ(StringSplit(s, " "));//공백을 기준으로 구문 분리
	string command;
	commandQ.Dequeue(command);
	
	if (command == "INSERT"){//INSERT시에

		commandQ.Dequeue(command);
		QueType<string> subQ(StringSplit(command, ","));//넘길 값들 subQ큐에 넣기
		
		table.Insert(subQ);
	}
	else if (command == "SELECT"){//SELECT시에
		table.Select(commandQ);
	}
	else if (command == "COMMIT") {//COMMIT시에
		table.Commit();
	}
	else if (command == "READ") {
		table.Read();
	}
}
