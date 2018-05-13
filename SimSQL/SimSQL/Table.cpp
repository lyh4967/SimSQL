#include "Table.h"

bool WhereProcessor(string sql, const string* fieldArr, int& index, string& compare);//조건자 처리
Table::Table(string name, int len, string field0, string field1, string field2) {//(테이블이름, 필드길이,필드명)
	listData = NULL;
	length = 0;
	tbl_name = name;
	fieldLen = len;
	fieldNames[0] = field0;
	fieldNames[1] = field1;
	fieldNames[2] = field2;
}

Table::~Table() {//destructer
	MakeEmpty();
}

void Table::MakeEmpty() {
	Tupl* tempTupl;

	while (listData != NULL)
	{
		tempTupl = listData;
		listData = listData->next;
		delete tempTupl;
	}
	length = 0;
}

void Table::Select(QueType<string>& sql) const {
	Tupl* location = listData;
	string tmpSQL;
	sql.Dequeue(tmpSQL);

	if (tmpSQL == "*") {// * 일경우 모든 필드 출력
		for (int i = 0; i < fieldLen; i++) {//필드명 출력
			cout << fieldNames[i] << ' ';
		}
		cout << endl;// 필드명 출력 후 줄바꿈
		if (!sql.IsEmpty()) {
			sql.Dequeue(tmpSQL);
			if (tmpSQL == "WHERE") {//조건이 있다면 if문으로
				int index;
				string compare;
				sql.Dequeue(tmpSQL);// tmpSQL:조건자체크문

				WhereProcessor(tmpSQL, fieldNames, index, compare);//해당필드인덱스, 비교대상을 받아옴

				for (int i = 0; i < length; i++) {//테이블의 크기만큼
												  //로그: cout << "log: " << location->infos[index] << ' ' << compare << endl;
					if (location->infos[index] == compare) {
						for (int i = 0; i < fieldLen; i++) { //조건에맞는 튜플출력
							cout << location->infos[i] << ' ';
						}
						cout << endl;
					}
					location = location->next;
				}
			}
		}
		else {//where 문이 없다면 전체 튜플 출력
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

void Table::Insert(QueType<string>& sql) {
	string value;
	int cnt = 0;
	Tupl* location = new Tupl;

	while (!sql.IsEmpty()) {//날아온 순서대로 value값을 tupl에 넣는다.
		sql.Dequeue(value);
		location->infos[cnt] = value;// tupl에 차례로 value 저장
		cnt++;
	}
	location->next = listData;
	listData = location;
	length++;
	cout << "SUCCESS!" << endl;

}
void Table::Commit() {
	string outputPath = tbl_name + ".dat";//테이블이름+ .dat에 쓰기
	output.open(outputPath, ios::out | ios::binary);
	Tupl* location = listData;

	while (!location == NULL) {
		output.write((char*)&location->infos, sizeof(location->infos));
		location = location->next;
	}
	output.close();
	cout << "SUCCESS!" << endl;
}

void Table::Read() {
	string inputPath = tbl_name + ".dat";//테이블이름 + .dat를 읽어옴
	input.open(inputPath, ios::in | ios::binary);
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

bool WhereProcessor(string sql, const string* fieldArr, int& index, string& compare) {
	QueType<string> tempQ = StringSplit(sql, "=");
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