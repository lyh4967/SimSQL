
#include <string>
#include <fstream>
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
	string fieldName[3];
	int length;//데이터 갯수
	ofstream output;
	ifstream input;
public:
	Table(string name, int len, string field0, string field1, string field2);//constructor
	//(테이블이름, 필드길이, 필드명)
	//현재는 테이블생성이 정적임

	void Select() const;//print 함수
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
	fieldName[0] = field0;
	fieldName[1] = field1;
	fieldName[2] = field2;
}

void Table::Select() const{
	Tupl* location = listData;
	for (int i = 0; i < fieldLen; i++){//필드명 출력
		cout << fieldName[i] << ' ';
	}
	cout << endl;

	for (int i = 0; i < length; i++){//테이블의 크기만큼
		for (int i = 0; i < fieldLen; i++){ //튜플 출력
			cout << location->infos[i] << ' ';
		}
		cout << endl;
		location = location->next;
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
	string outputPath = tbl_name + ".bin";
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
	string inputPath = tbl_name + ".bin";
	input.open(inputPath,ios::in|ios::binary);
	length = 0;
	while (!input.eof()) {
		Tupl* location = new Tupl;
		input.read((char*)& location->infos, sizeof(location->infos));
		location->next = listData;
		listData = location;
		length++;
	}
	input.close();
	cout << "SUCCESS! READ" << endl;

}