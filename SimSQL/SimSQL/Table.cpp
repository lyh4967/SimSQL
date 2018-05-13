#include "Table.h"

bool WhereProcessor(string sql, const string* fieldArr, int& index, string& compare);//������ ó��
Table::Table(string name, int len, string field0, string field1, string field2) {//(���̺��̸�, �ʵ����,�ʵ��)
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

	if (tmpSQL == "*") {// * �ϰ�� ��� �ʵ� ���
		for (int i = 0; i < fieldLen; i++) {//�ʵ�� ���
			cout << fieldNames[i] << ' ';
		}
		cout << endl;// �ʵ�� ��� �� �ٹٲ�
		if (!sql.IsEmpty()) {
			sql.Dequeue(tmpSQL);
			if (tmpSQL == "WHERE") {//������ �ִٸ� if������
				int index;
				string compare;
				sql.Dequeue(tmpSQL);// tmpSQL:������üũ��

				WhereProcessor(tmpSQL, fieldNames, index, compare);//�ش��ʵ��ε���, �񱳴���� �޾ƿ�

				for (int i = 0; i < length; i++) {//���̺��� ũ�⸸ŭ
												  //�α�: cout << "log: " << location->infos[index] << ' ' << compare << endl;
					if (location->infos[index] == compare) {
						for (int i = 0; i < fieldLen; i++) { //���ǿ��´� Ʃ�����
							cout << location->infos[i] << ' ';
						}
						cout << endl;
					}
					location = location->next;
				}
			}
		}
		else {//where ���� ���ٸ� ��ü Ʃ�� ���
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

void Table::Insert(QueType<string>& sql) {
	string value;
	int cnt = 0;
	Tupl* location = new Tupl;

	while (!sql.IsEmpty()) {//���ƿ� ������� value���� tupl�� �ִ´�.
		sql.Dequeue(value);
		location->infos[cnt] = value;// tupl�� ���ʷ� value ����
		cnt++;
	}
	location->next = listData;
	listData = location;
	length++;
	cout << "SUCCESS!" << endl;

}
void Table::Commit() {
	string outputPath = tbl_name + ".dat";//���̺��̸�+ .dat�� ����
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
	string inputPath = tbl_name + ".dat";//���̺��̸� + .dat�� �о��
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
	tempQ.Dequeue(tmpStr);//���� �ʵ�

	for (int i = 0; i < (int)fieldArr->size(); i++) {
		if (fieldArr[i] == tmpStr)
			index = i;
	}

	tempQ.Dequeue(tmpStr);

	compare = tmpStr;//���� ���
	return true;

}