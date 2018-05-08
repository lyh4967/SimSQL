
#include <string>
#include <fstream>
using namespace std;
struct Tupl{
	string infos[5];
	Tupl* next;
	Tupl* prev;
};

class Table {
private:
	int info;
	Tupl* listData;
	string tbl_name;
	string field[5];
	int length;
public:
	Table(){
		listData = NULL;
		length = 0;
	}
	void Print(){
		std::cout << info;
	}
	void Insert(string sql){
		Tupl* location = new Tupl;
		location->infos[0] = sql;// 요소 저장
		location->next = listData;
		listData = location;
	}
	void commit(std::ofstream& out){
		out.write((char*)&info,sizeof(int));
	}
	void read(std::ifstream& in){
		in.read((char*)&info, sizeof(int));
	}
};
