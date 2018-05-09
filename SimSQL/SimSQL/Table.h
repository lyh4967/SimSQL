
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
	int length;//데이터 갯수
	ofstream output;
	ifstream input;
public:
	Table(string name, int len, string field0, string field1, string field2);//constructor
	//(테이블이름, 필드길이, 필드명)
	//현재는 테이블생성이 정적임

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
Table::Table(string name, int len, string field0, string field1, string field2){//(테이블이름, 필드길이,필드명)
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
	tempQ.Dequeue(tmpStr);//조건 필드

	for (int i = 0; i < (int)fieldArr->size(); i++) {
		if (fieldArr[i] == tmpStr)
			index = i;
	}

	tempQ.Dequeue(tmpStr);

	compare = tmpStr;//조건 대상
	return true;

}

void Table::Select(QueType<string>& sql) const{
	Tupl* location = listData;
	string tmpSQL;
	sql.Dequeue(tmpSQL);

	if (tmpSQL == "*") {// * 일경우 모든 필드 출력
		for (int i = 0; i < fieldLen; i++) {//필드명 출력
			cout << fieldNames[i] << ' ';
		}
		cout << endl;
		if (!sql.IsEmpty()) {
			sql.Dequeue(tmpSQL);
			if (tmpSQL == "WHERE") {
				int index;
				string compare;
				sql.Dequeue(tmpSQL);// tmpSQL:조건자체크문

				WhereProcessor(tmpSQL, fieldNames, index, compare);//해당필드인덱스, 비교대상을 받아옴
				cout << "log: " << location->infos[index] << ' ' << compare << endl;
				for (int i = 0; i < length; i++) {//테이블의 크기만큼
					if (location->infos[index] == compare) {
						for (int i = 0; i < fieldLen; i++) { //조건에맞는 튜플출력
							cout << location->infos[i] << ' ';
						}
						cout << endl;
						location = location->next;
					}
				}
			}
		}
		else {//where 문이 없다면
			for (int i = 0; i < length; i++) {//테이블의 크기만큼
				for (int i = 0; i < fieldLen; i++) { //전체 튜플 출력
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

	while (!sql.IsEmpty()){//날아온 순서대로 value값을 tupl에 넣는다.
		sql.Dequeue(value);
		location->infos[cnt] = value;// tupl에 차례로 value 저장
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


