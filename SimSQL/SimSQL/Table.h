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
	int length;//������ ����
	ofstream output;
	ifstream input;
public:
	Table(string name, int len, string field0, string field1, string field2);//constructor
	//(���̺��̸�, �ʵ����, �ʵ��)
	//����� ���̺������ ������

	~Table();//destructer

	void MakeEmpty();
	//pre: table�� �ʱ�ȭ�Ǿ��ִ�.
	//post: �޸𸮻� table������ �������

	void Select(QueType<string>& sql) const;//print �Լ�
	//pre: table�� �ʱ�ȭ �Ǿ��ִ�,
	//post: table�� �ִ� �ʵ��� tupl�� ����Ѵ�.
	
	void Insert(QueType<string>& sql);
	//pre: sql�� �ʱ�ȭ�Ǿ��ִ�.
	//post: tupl�� �߰��ȴ�.

	void Commit();
	//pre: table�� �ʱ�ȭ�Ǿ��ִ�.
	//post: out���Ͽ� ���̺������� ��������.

	void Read();
	//pre: input�� �ʱ�ȭ�Ǿ� �־���Ѵ�.
	//post: ���̺��� �̸��� ���̳ʸ������� �ҷ��� ������ �д´�
};



