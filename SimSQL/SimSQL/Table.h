
#include <string>
#include <fstream>
#include "SubFunc.h"
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
Table::Table(string name, int len, string field0, string field1, string field2){//(���̺��̸�, �ʵ����,�ʵ��)
	listData = NULL;
	length = 0;
	tbl_name = name;
	fieldLen = len;
	fieldNames[0] = field0;
	fieldNames[1] = field1;
	fieldNames[2] = field2;
}

bool WhereProcessor(string sql,const string* fieldArr,int& index,string& compare) {
	QueType<string> tempQ = StringSplit(sql,"=");
	string tmpStr;
	tempQ.Dequeue(tmpStr);//���� �ʵ�

	for (int i = 0; i < (int)fieldArr->size(); i++) {
		if (fieldArr[i] == tmpStr)
			index = i;
	}

	tempQ.Dequeue(tmpStr);

	compare = tmpStr;//���� ���
	return true;

}

void Table::Select(QueType<string>& sql) const{
	Tupl* location = listData;
	string tmpSQL;
	sql.Dequeue(tmpSQL);

	if (tmpSQL == "*") {// * �ϰ�� ��� �ʵ� ���
		for (int i = 0; i < fieldLen; i++) {//�ʵ�� ���
			cout << fieldNames[i] << ' ';
		}
		cout << endl;
		if (!sql.IsEmpty()) {
			sql.Dequeue(tmpSQL);
			if (tmpSQL == "WHERE") {
				int index;
				string compare;
				sql.Dequeue(tmpSQL);// tmpSQL:������üũ��

				WhereProcessor(tmpSQL, fieldNames, index, compare);//�ش��ʵ��ε���, �񱳴���� �޾ƿ�
				cout << "log: " << location->infos[index] << ' ' << compare << endl;
				for (int i = 0; i < length; i++) {//���̺��� ũ�⸸ŭ
					if (location->infos[index] == compare) {
						for (int i = 0; i < fieldLen; i++) { //���ǿ��´� Ʃ�����
							cout << location->infos[i] << ' ';
						}
						cout << endl;
						location = location->next;
					}
				}
			}
		}
		else {//where ���� ���ٸ�
			for (int i = 0; i < length; i++) {//���̺��� ũ�⸸ŭ
				for (int i = 0; i < fieldLen; i++) { //��ü Ʃ�� ���
					cout << location->infos[i] << ' ';
				}
				cout << endl;
				location = location->next;
			}
		}
	}
	
	
	
}

void Table::Insert(QueType<string>& sql){
	string value;
	int cnt = 0;
	Tupl* location = new Tupl;

	while (!sql.IsEmpty()){//���ƿ� ������� value���� tupl�� �ִ´�.
		sql.Dequeue(value);
		location->infos[cnt] = value;// tupl�� ���ʷ� value ����
		cnt++;
	}
	location->next = listData;
	listData = location;
	length++;
	cout << "SUCCESS!" << endl;

}
void Table::Commit(){
	string outputPath = tbl_name + ".dat";
	output.open(outputPath,ios::out|ios::binary);
	Tupl* location = listData;

	while (!location == NULL) {
		output.write((char*)&location->infos, sizeof(location->infos));
		location = location->next;
	}
	output.close();
	cout << "SUCCESS!" << endl;
}

void Table::Read() {
	string inputPath = tbl_name + ".dat";
	input.open(inputPath,ios::in|ios::binary);
	length = 0;
	Tupl* location = new Tupl;
	while (input.read((char*)& location->infos, sizeof(location->infos))) {
		location->next = listData;
		listData = location;
		length++;
		location = new Tupl;
	}
	input.close();
	cout << "SUCCESS! READ" << endl;

}


