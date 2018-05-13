#pragma once
#include "SubFunc.h"
#include "myLib.h"
using namespace std;
struct Tupl{
	string infos[3];
	Tupl* next;
	Tupl* prev;
};

class Table {
private:
	Tupl* listData;
	string tbl_name;
	int fieldLen;
	string fieldNames[3];
	int length;//데이터 갯수
	ofstream output;
	ifstream input;
public:
	Table(string name, int len, string field0, string field1, string field2);//constructor
	//(테이블이름, 필드길이, 필드명)
	//현재는 테이블생성이 정적임

	~Table();//destructer

	void MakeEmpty();
	//pre: table은 초기화되어있다.
	//post: 메모리상 table정보는 사라진다

	void Select(QueType<string>& sql) const;//print 함수
	//pre: table는 초기화 되어있다,
	//post: table에 있는 필드명과 tupl을 출력한다.
	
	void Insert(QueType<string>& sql);
	//pre: sql은 초기화되어있다.
	//post: tupl이 추가된다.

	void Commit();
	//pre: table는 초기화되어있다.
	//post: out파일에 테이블정보가 쓰여진다.

	void Read();
	//pre: input는 초기화되어 있어야한다.
	//post: 테이블의 이름의 바이너리파일을 불러와 정보를 읽는다
};



