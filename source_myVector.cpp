#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <utility>

#define OutOfRangeException 1

using std::cout;
using std::endl;
using std::string;

// class Timer len rucne prepisane z prednasky
class Timer
{
public:
	static std::chrono::time_point<std::chrono::high_resolution_clock> t_start; // zaciatok pocitania
	static std::chrono::time_point<std::chrono::high_resolution_clock> t_end; // koniec pocitania

	static void start() { t_start = std::chrono::high_resolution_clock::now(); }
	static void end(string message) { t_end = std::chrono::high_resolution_clock::now(); print(message); }

	static void print(string s)
	{
		cout << std::fixed << std::setprecision(2) << s << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms/n";
	}
};

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_start = std::chrono::high_resolution_clock::now();
std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_end = std::chrono::high_resolution_clock::now();

template<class T>
class myVector
{
private:
	T* data;
	int length;
public:
	myVector() { data = nullptr; length = 0; } // prazdny konstruktor
	myVector(int length, T defaultValue); // kostruktor s parametrami
	~myVector() { delete[] data; } //destruktor

	int Length() { return length; }

	void resize(int newLength);
	T& at(int index);
	T& operator [](int index) { return data[index]; }
	void push_back(T newValue);
	T& begin() { return data[0]; }
	T& end() { return data[length - 1]; }
	void clear();

	void printData();
};

template<class T>
myVector<T>::myVector(int length, T defaultValue)
{
	try
	{
		data = new T[length]; // skusi allokovat miesto
	}
	catch (std::bad_alloc error)
	{
		cout << "Not enough memory" << endl; // ak sa nenajde, tak je vrati exception?
		delete[] data;
		return;
	}

	//cout << "Allocation successful" << endl;

	this->length = length; // priradenie dlzky vektora
	
	for (int i = 0; i < this->length; i++)
		data[i] = defaultValue; // naplnenie vektora defaultnymi hodnotami
}

template<class T>
void myVector<T>::resize(int newLength)
{
	T* newData = nullptr;
	
	try
	{
		newData = new T[newLength];
	}
	catch (std::bad_alloc error)
	{
		cout << "Not enough memory" << endl;
		delete[] newData;
		return;
	}
	
	//cout << "Allocation successful" << endl;

	if (length >= newLength) // > / >= ?
	{
		for (int i = 0; i < newLength; i++)
			newData[i] = data[i]; // prekopiruju sa iba tie data, co sa zmestia do noveho vektora
	}
	else if (length < newLength)
	{
		for (int i = 0; i < length; i++)
			newData[i] = data[i]; // prekopiruju sa vsetky data, nejake miesta v novom vektore budu prazdne

		for (int i = length; i < newLength; i++)
			newData[i] = NULL; // zvysne miesta sa zaplnia ako NULL
	}

	delete[] data; // deallokuje sa miesto, kde ukazuje smernik data
	data = newData; // smernik newData sa priradi do zmernika data, cize data bude ukazovat na nove miesto v pamati
	length = newLength; // zmena starej length na newLength
}

template<class T>
T& myVector<T>::at(int index)
{
	if (index < 0 || index >= length)
		throw OutOfRangeException; // ak je zadany zly index, tak hodi exception

	return data[index];
}


template<class T>
void myVector<T>::push_back(T newValue)
{
}

template<class T>
void myVector<T>::clear()
{
	for (int i = 0; i < length; i++)
		data[i] = NULL; // priradenie NULL hodnoty namiesto ulozenych hodnot

	delete[] data; // deallokacia miesta
	data = nullptr; // pointer nebude ukazovat na nijake miesto
}

template<class T>
void myVector<T>::printData()
{
	cout << "myVektor = (";

	for (int i = 0; i < length; i++)
	{
		if (i + 1 != length)
			cout << data[i] << ", ";
		else
			cout << data[i];
	}

	cout << ")" << endl;
}

int main()
{
	myVector<int> vector(10, 1);
	vector.printData();

	vector.resize(14);
	vector.printData();

	return 0;
}