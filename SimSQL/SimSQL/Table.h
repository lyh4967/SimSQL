
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
	int length;//������ ����
	ofstream output;
	ifstream input;
public:
	Table(string name, int len, string field0, string field1, string field2);//constructor
	//(���̺��̸�, �ʵ����, �ʵ��)
	//����� ���̺������ ������

	void Select() const;//print �Լ�
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
	fieldName[0] = field0;
	fieldName[1] = field1;
	fieldName[2] = field2;
}

void Table::Select() const{
	Tupl* location = listData;
	for (int i = 0; i < fieldLen; i++){//�ʵ�� ���
		cout << fieldName[i] << ' ';
	}
	cout << endl;

	for (int i = 0; i < length; i++){//���̺��� ũ�⸸ŭ
		for (int i = 0; i < fieldLen; i++){ //Ʃ�� ���
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