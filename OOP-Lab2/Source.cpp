#include "iostream"
#include "list"
#include "cstring"

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"

using namespace std;

class VectorBit {
private:
	unsigned char* mas;
	int n_bit;
	int size;

	static int countVector;
	list<int> bit_changed;
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
 * @brief Конструктор за замовченням
*/
VectorBit::VectorBit() {
	
	n_bit = 60;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	countVector++;
}

/**
 * @brief Параметричний конструктор
 * @param bits Кількість бітів для створення бітового вектора
*/
VectorBit::VectorBit(int& bits) {

	n_bit = bits;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	countVector++;
}

/**
 * @brief Конструктор для ініціалізації за допомогою значення наданого символьним рядком
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
 * @brief Конструктор копії
 * @param obj Об'єкт, з якого потрібно створити копію
*/
VectorBit::VectorBit(const VectorBit& obj) {
	
	n_bit = obj.n_bit;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	for (int i = 0; i < size; i++) {
		mas[i] = obj.mas[i];
	}
	bit_changed = obj.bit_changed;
	countVector++;
}

/**
 * @brief Метод-сеттер, заповнення бітового вектора значеннями
*/
void VectorBit::SetVector() {

	if (!this->bit_changed.empty()) {
		this->bit_changed.clear();
	}

	for (int i = 0; i < this->n_bit; i++) {
		int x = rand() % 2;
		if (x == 0) this->mas[i / 8] &= ~(1 << (i % 8));
		else if (x == 1) this->mas[i / 8] |= (1 << (i % 8));
	}
}

/**
 * @brief Метод, який використовується для встановлення біта з заданим номером в 0
 * @param x Місце розташування біта в бітовому векторі
*/
void VectorBit::Set0(int x) {

	if (x != 0 && x <= this->n_bit) {
		this->bit_changed.push_back(x);
		x--;
		this->mas[x / 8] &= ~(1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;	
}

/**
 * @brief Метод, який використовується для встановлення біта з заданим номером в 1
 * @param x Місце розташування біта в бітовому векторі
*/
void VectorBit::Set1(int x) {

	if (x != 0 && x <= this->n_bit) {
		this->bit_changed.push_back(x);
		x--;
		this->mas[x / 8] |= (1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief Метод, який використовується для інвертування біта з наданим номером
 * @param x Місце розташування біта в бітовому векторі
*/
void VectorBit::Flip(int x) {

	if (x != 0 && x <= this->n_bit) {
		this->bit_changed.push_back(x);
		x--;
		this->mas[x / 8] ^= (1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief Метод, який використовується для виведення бітового вектора на екран
*/
void VectorBit::Show() {

	for (int i = 0; i < this->n_bit; i++) {
		list<int>::iterator it = find(this->bit_changed.begin(), this->bit_changed.end(), i + 1);
		if (it != this->bit_changed.end()) cout << ANSI_COLOR_BLUE << ((this->mas[i / 8] >> (i % 8)) & 1) << ANSI_COLOR_RESET;
		else cout << ((this->mas[i / 8] >> (i % 8)) & 1);
		if ((i + 1) % 8 == 0) cout << "|";
		else if ((i + 1) % 4 == 0) cout << " ";
	}
	cout << endl;
}

/**
 * @brief Метод, який повертає розмір бітового вектора у бітах
 * @return Розмір бітового вектора у бітах та кількість байтів, використанні для зберігання цього вектора
*/
pair<int, int> VectorBit::Size() {

	return make_pair(this->n_bit, this->size);
}

/**
 * @brief Деструктор
*/
VectorBit::~VectorBit() {

	cout << "\nThe VectorBit #" << countVector << " was destroyed" << endl;
	delete[] mas;
	countVector--;
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки
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
	const char* str = "10001110011";

	cout << "Enter lenght of bit vector v2: ";
	cin >> bits;

	VectorBit v1, v2(bits), v4(str);
	VectorBit v3 = v4;

	while (work == 1) {
		switch (work) {
		case 1:
			v1.SetVector();
			cout << "Bit vector v1: ";
			v1.Show();
			v1.Set0(6);
			cout << "Bit vector v1: ";
			v1.Show();
			v1.Set0(32);
			cout << "Bit vector v1: ";
			v1.Show();
			v1.Set1(1);
			cout << "Bit vector v1: ";
			v1.Show();
			v2.SetVector();
			cout << "Bit vector v2: ";
			v2.Show();
			v2.Flip(10);
			v2.Flip(5);
			v2.Flip(3);
			cout << "Bit vector v2: ";
			v2.Show();
			cout << "Bit vector v4: ";
			v4.Show();
			cout << "Bit vector v3: ";
			v3.Show();
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