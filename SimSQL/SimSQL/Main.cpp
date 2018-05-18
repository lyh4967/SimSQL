#include "SubFunc.h"
#include "Table.h"
#include "myLib.h"
#include "Schema.h"
#include "SQLProcessor.h"


int main(){

	ifstream commandInput("commandSQL.txt");
	Table table("test",3,"�й�","�̸�","�б�");//���̺�(���̺��̸�, �ʵ����,�ʵ��)
	Schema schema;
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
