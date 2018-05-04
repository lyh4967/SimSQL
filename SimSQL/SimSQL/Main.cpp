#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include"QueType.h"
#include "Table.h"
#define D_MAX_ARRAY_SIZE 100
using namespace std;

void SQLProcessor(string s);

int main(){

	//ofstream output("data.bin", ios::out | ios::binary);
	//ifstream input("data.bin", ios::in | ios::binary);
	cout << "Hello customer, This is SimSQL" << endl;
	bool flag = true;
	string sql;
	while (flag){
		cout << ">";
		getline(cin, sql);
		SQLProcessor(sql);
		flag = false;
	}
	return 0;
}
QueType<string> StringSplit(string strTarget, string strTok)
{
	int     nCutPos;
	int     nIndex = 0;
	QueType<string> Que;

	while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
	{
		if (nCutPos > 0)
		{
			Que.Enqueue(strTarget.substr(0, nCutPos));
		}
		strTarget = strTarget.substr(nCutPos + 1);
	}

	if (strTarget.length() > 0)
	{
		Que.Enqueue(strTarget.substr(0, nCutPos));
	}
	
	return Que;
}

void SQLProcessor(string s){
	/*vector<string> tokens;
	istringstream iss(s);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));*/
	QueType<string> tempQ (StringSplit(s, " "));
	while (!tempQ.IsEmpty()){
		string tmp;
		tempQ.Dequeue(tmp);
		cout << tmp<<endl;
	}

	
}