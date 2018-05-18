#include "SubFunc.h"
#include "Table.h"
#include "myLib.h"
#include "Schema.h"
#include "SQLProcessor.h"


int main(){

	ifstream commandInput("commandSQL.txt");
	Table table("test",3,"학번","이름","학교");//테이블(테이블이름, 필드길이,필드명)
	Schema schema;
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
