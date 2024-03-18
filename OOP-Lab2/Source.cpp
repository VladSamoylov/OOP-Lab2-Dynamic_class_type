#include "iostream"
#include "list"
#include "cstring"
#include "iomanip"

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"

using namespace std;

class Node {
private:
	Node* ptr_next;
	Node* ptr_prev;
	int data;
	friend class DoublyLinkedList;
};

class DoublyLinkedList {
private:
	Node* root_head;
	Node* root_tail;
	int n_count;
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList&);
	void PushBack(int);
	Node* Next(Node*);
	Node* Prev(Node*);
	void Show();
	void Clear();
	bool isFind(int);
	void DeleteSelectNode(int);
	bool isEmpty() { return this->root_head == NULL && this->root_tail == NULL; }
	int Lenght() { return this->n_count; }
	int GetValue(Node* ptr) { return ptr->data; }
	~DoublyLinkedList() { Clear(); }
};

/**
 * @brief ����������� �� ����������� �����'������ ������
*/
DoublyLinkedList::DoublyLinkedList() {

	root_head = NULL;
	root_tail = NULL;
	n_count = 0;
}

/**
 * @brief ����������� ��ﳿ
 * @param list ��'���, � ����� ������� �������� ����
*/
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list) {

	n_count = list.n_count;
	if (list.n_count == 0) {
		root_head = list.root_head;
		root_tail = list.root_tail;
	}
	else {
		Node* p = list.root_head;
		do {
			Node* node = new Node();			
			node->data = p->data;			
			if (isEmpty()) {
				root_head = node;
				root_tail = node;
				node->ptr_next = NULL;
				node->ptr_prev = NULL;
			}
			else {
				Node* p = root_tail;
				p->ptr_next = node;
				node->ptr_prev = root_tail;
				node->ptr_next = NULL;
				root_tail = node;
			}
			p = p->ptr_next;
		} while (p != NULL);
	}
}

/**
 * @brief �����, ���� ������ ����� � �������� ���� � ����� ������
 * @param data ��� ��� �������� �� ������
*/
void DoublyLinkedList::PushBack(int data) {

	Node* new_node = new Node();
	new_node->data = data;
	n_count++;

	if (this->isEmpty()) {
		this->root_head = new_node;
		this->root_tail = new_node;
		new_node->ptr_next = NULL;
		new_node->ptr_prev = NULL;
	}
	else {
		Node* p = this->root_tail;
		p->ptr_next = new_node;
		new_node->ptr_prev = this->root_tail;
		new_node->ptr_next = NULL;
		this->root_tail = new_node;
	}
}

/**
 * @brief �����, ���� ������ ������� �� ��������� ����� ������
 * @param node �������� ����� ������
 * @return ���������� ����� ������
*/
Node* DoublyLinkedList::Next(Node* node) {

	if (node == NULL) {
		return NULL;
	}
	if (this->root_tail == node) {
		return NULL;
	}

	return node->ptr_next;
}

/**
 * @brief �����, ���� ������ ������� �� ��������� ����� ������
 * @param node �������� ����� ������
 * @return ��������� ����� ������
*/
Node* DoublyLinkedList::Prev(Node* node) {

	if (node == NULL) {
		return NULL;
	}
	if (this->root_head == node) {
		return NULL;
	}

	return node->ptr_prev;
}

/**
 * @brief �����, ���� ������ ����� �������� � ������
 * @param x ������� ��� ������
 * @return True, ���� ������� ���� ��������
*/
bool DoublyLinkedList::isFind(int x) {

	Node* p = this->root_tail;
	if (p == NULL) {
		return false;
	}
	while (p != NULL) {
		if (p->data == x) return true;
		p = this->Prev(p);
	}
	return false;
}

/**
 * @brief �����, ���� �������� ��������, �� �������� � ������
*/
void DoublyLinkedList::Show() {

	Node* p = this->root_head;
	
	while (p != NULL) {
		cout << p->data << " ";
		p = this->Next(p);
	} cout << endl;
}

/**
 * @brief �����, ���� ������� ����� ������
*/
void DoublyLinkedList::Clear() {

	Node* p = this->root_tail;

	if (p == NULL) {
		return;
	}
	do
	{
		Node* d = p;
		p = this->Prev(p);
		delete d;
		this->n_count--;
	} while (p != NULL);
	this->root_head = NULL;
	this->root_tail = NULL;
}

/**
 * @brief �����, ���� ������� ������� �����
 * @param n ������� �����
*/
void DoublyLinkedList::DeleteSelectNode(int n) {

	if (n < this->n_count && n >= 0) {
		Node* c = this->root_head;
		if (c == NULL) return;
		while (n != 0) {
			c = this->Next(c);
			n--;
		}
		Node* prev = this->Prev(c);
		Node* next = this->Next(c);
		if (c == this->root_head && c == this->root_tail) {
			this->root_head = NULL;
			this->root_tail = NULL;
		}
		else if (c == this->root_head) {
			this->root_head = next;
			next->ptr_prev = NULL;
		}
		else if (c == this->root_tail) {
			this->root_tail = prev;
			prev->ptr_next = NULL;
		}
		else {
			prev->ptr_next = next;
			next->ptr_prev = prev;
		}
		delete c;
		this->n_count--;
	} else cerr << "Error!The requested NODE was not found !" << endl;
}


class VectorBit {
private:
	unsigned char* mas;
	int n_bit;
	int size;

	static int countVector;
	//list<int> bit_changed;
	DoublyLinkedList bit_changedlist;
public:
	VectorBit();
	VectorBit(int&);
	VectorBit(const char*);
	VectorBit(const VectorBit&);
	void SetVector();
	void Set0(int);
	void Set1(int);
	void Flip(int);
	void Show();
	pair<int,int> Size();
	~VectorBit();
};

int VectorBit::countVector = 0;

/**
 * @brief ����������� �� �����������
*/
VectorBit::VectorBit() {
	
	n_bit = 60;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	countVector++;
}

/**
 * @brief ������������� �����������
 * @param bits ʳ������ ��� ��� ��������� ������� �������
*/
VectorBit::VectorBit(int& bits) {

	n_bit = bits;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	countVector++;
}

/**
 * @brief ����������� ��� ����������� �� ��������� �������� �������� ���������� ������
 * @param str 
*/
VectorBit::VectorBit(const char* str) {

	n_bit = strlen(str);
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];

	for (int i = 0; i < n_bit; i++) {
		if (str[i] == '1') mas[i / 8] |= (1 << (i % 8));
		else mas[i / 8] &= ~(1 << (i % 8));
	}
	countVector++;
}

/**
 * @brief ����������� ��ﳿ
 * @param obj ��'���, � ����� ������� �������� ����
*/
VectorBit::VectorBit(const VectorBit& obj) {
	
	n_bit = obj.n_bit;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	for (int i = 0; i < size; i++) {
		mas[i] = obj.mas[i];
	}
	//bit_changed = obj.bit_changed;
	bit_changedlist = obj.bit_changedlist;
	countVector++;
}

/**
 * @brief �����-������, ���������� ������� ������� ����������
*/
void VectorBit::SetVector() {

	/*if (!this->bit_changed.empty()) {
		this->bit_changed.clear();
	}*/
	if (!this->bit_changedlist.isEmpty()) {
		this->bit_changedlist.Clear();
	}

	for (int i = 0; i < this->n_bit; i++) {
		int x = rand() % 2;
		if (x == 0) this->mas[i / 8] &= ~(1 << (i % 8));
		else if (x == 1) this->mas[i / 8] |= (1 << (i % 8));
	}
}

/**
 * @brief �����, ���� ��������������� ��� ������������ ��� � ������� ������� � 0
 * @param x ̳��� ������������ ��� � ������� ������
*/
void VectorBit::Set0(int x) {

	if (x != 0 && x <= this->n_bit) {
		//this->bit_changed.push_back(x);
		this->bit_changedlist.PushBack(x);
		x--;
		this->mas[x / 8] &= ~(1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;	
}

/**
 * @brief �����, ���� ��������������� ��� ������������ ��� � ������� ������� � 1
 * @param x ̳��� ������������ ��� � ������� ������
*/
void VectorBit::Set1(int x) {

	if (x != 0 && x <= this->n_bit) {
		//this->bit_changed.push_back(x);
		this->bit_changedlist.PushBack(x);
		x--;
		this->mas[x / 8] |= (1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief �����, ���� ��������������� ��� ������������ ��� � ������� �������
 * @param x ̳��� ������������ ��� � ������� ������
*/
void VectorBit::Flip(int x) {

	if (x != 0 && x <= this->n_bit) {
		//this->bit_changed.push_back(x);
		this->bit_changedlist.PushBack(x);
		x--;
		this->mas[x / 8] ^= (1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief �����, ���� ��������������� ��� ��������� ������� ������� �� �����
*/
void VectorBit::Show() {

	for (int i = 0; i < this->n_bit; i++) {
		//list<int>::iterator it = find(this->bit_changed.begin(), this->bit_changed.end(), i + 1);
		if (this->bit_changedlist.isFind(i + 1)) cout << ANSI_COLOR_BLUE << ((this->mas[i / 8] >> (i % 8)) & 1) << ANSI_COLOR_RESET;
		else cout << ((this->mas[i / 8] >> (i % 8)) & 1);
		if ((i + 1) % 8 == 0) cout << "|";
		else if ((i + 1) % 4 == 0) cout << " ";
	}
	cout << endl;
}

/**
 * @brief �����, ���� ������� ����� ������� ������� � ����
 * @return ����� ������� ������� � ���� �� ������� �����, ����������� ��� ��������� ����� �������
*/
pair<int, int> VectorBit::Size() {

	return make_pair(this->n_bit, this->size);
}

/**
 * @brief ����������
*/
VectorBit::~VectorBit() {

	cout << "\nThe VectorBit #" << countVector << " was destroyed" << endl;
	delete[] mas;
	countVector--;
}

/**
 * @brief �������, ��� �������� ����������� �������� ����� ������������
 * @param x ���� ��� ��������
*/
void CheckData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cout << "Enter lenght of bit vector: ";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

int main() {
	srand(time(0));
	int bits = 0;
	int work = 1;
	const char* str = "1200sadsa132120211";

	cout << "Enter lenght of bit vector v2: ";
	cin >> bits;
	CheckData(bits);

	VectorBit v1, v2(bits), v4(str);
	VectorBit v3 = v4;
	//DoublyLinkedList l;
	//cout << l.Lenght() << endl;
	//l.PushBack(50);
	//l.Show();
	//l.PushBack(100);
	//for (int i = 0; i < bits + 1; i++) {
	//	l.PushBack(100 + i * 10);
	//}
	//l.Show();
	//cout << l.Lenght() << endl;
	//cout << l.isFind(3) << endl;
	//l.Clear();
	//for (int i = 0; i < bits + 1; i++) {
	//	l.PushBack(100 + i * 10);
	//}
	//DoublyLinkedList l2 = l;
	////l.Clear();
	//l.Show();
	//cout << l.Lenght() << endl;	
	//l2.Show();
	//cout << l2.Lenght() << endl;
	//l2.DeleteSelectNode(0);
	//l2.Show();
	//cout << l2.Lenght() << endl;
	//l2.DeleteSelectNode(9);
	//l2.Show();
	//cout << l2.Lenght() << endl;
	//l2.DeleteSelectNode(4);
	//l2.Show();
	//cout << l2.Lenght() << endl;
	//l.Show();
	//cout << l.Lenght() << endl;

	while (work == 1) {
		switch (work) {
		case 1:
			v1.SetVector();
			cout << setw(35) << left << "Bit vector v1: "; v1.Show();
			v1.Set0(6);
			cout << setw(35) << left << "Bit vector v1 (set 6 bit to 0): "; v1.Show();
			v1.Set0(32);
			cout << setw(35) << left << "Bit vector v1 (set 32 bit to 0): "; v1.Show();
			v1.Set1(1);
			cout << setw(35) << left << "Bit vector v1 (set 1 bit to 1): "; v1.Show();
			v1.Set1(60);
			cout << setw(35) << left << "Bit vector v1 (set 60 bit to 1): "; v1.Show();
			v2.SetVector();
			cout << setw(36) << left << "Bit vector v2: "; v2.Show();
			v2.Flip(10);
			v2.Flip(5);
			v2.Flip(3);
			cout << setw(36) << left << "Bit vector v2 (flip 10, 5, 3 bits): "; v2.Show();
			cout << setw(43) << left << "Bit vector v4 (str = 1200sadsa132120211): "; v4.Show();
			cout << setw(43) << left << "Bit vector v3 (copy of v4): "; v3.Show();			
			cout << "Size of Bit vector v3: " << v3.Size().first << " bit(s) / This vector takes up: " << v3.Size().second << " byte(s) in memory" << endl;
			break;
		case 0:
			work = 0;
			break;
		default:
			work = 0;
			break;
		}
		cout << "\n------Retry? 1 - Yes / 0 - No------\n";
		cin >> work;
			
	}
	return 0;
}