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
		cout << std::fixed << std::setprecision(2) << s << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms/n" << endl;
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
		cout << "Allocation failed" << endl; // ak sa nenajde, tak je vrati exception?
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
		cout << "Allocation failed" << endl;
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
	try
	{
		if (index < 0 || index >= length)
			throw OutOfRangeException; // ak je zadany zly index, tak hodi exception
	}
	catch (int error)
	{
		if (error == OutOfRangeException)
			cout << "Incorrect index" << endl;
	}

	return data[index];
}


template<class T>
void myVector<T>::push_back(const T newValue) // toto je vypoctovo narocne
{
	T* newData = nullptr;
	int temp = length + 1;
	try
	{
		newData = new T[temp];
	}
	catch (std::bad_alloc)
	{
		cout << "Allocation failed" << endl;
		delete[] newData;
		return;
	}

	for (int i = 0; i < length + 1; i++)
	{
		if (i != length)
			newData[i] = data[i]; // prekopirovanie zo stareho pointera do noveho pointera
		else
			newData[i] = newValue; // pridanie novej hodnoty na posledne miesto v newData, cize na index length, lebo celu dlzku ma length + 1
	}

	delete[] data; // deallokacia starych dat
	data = newData; // priradenie noveho pointera s novymi datami, kde je aj ta nova hodnota
	length = length + 1; // zvysenie dlzky vektora o 1
}

template<class T>
void myVector<T>::clear()
{
	for (int i = 0; i < length; i++)
		data[i] = NULL; // priradenie NULL hodnoty namiesto ulozenych hodnot

	delete[] data; // deallokacia miesta
	data = nullptr; // pointer nebude ukazovat na nijake miesto

	cout << "clear done" << endl;
}

template<class T>
void myVector<T>::printData()
{
	cout << "myVector = (";

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
	int tempSum = 0;

	cout << "Class myVector:" << endl;

	Timer::start();
	myVector<int> vector(10000000, 1);
	//vector.printData();
	for (int i = 0; i < vector.Length(); i++)
		tempSum += vector[i];

	cout << "Suma prvkov myVector: " << tempSum << endl;

	vector.resize(20000000);
	cout << "resize done" << endl;
	//vector.printData();

	//cout << "Begin: " << vector.begin() << endl << "End: " << vector.end() << endl << "Index = 3: " << vector[3] << endl << "At(13): " << vector.at(13) << endl;

	/*try
	{
		vector.at(vector.Length() + 1);
	}
	catch (int error)
	{
		if (error == OutOfRangeException)
			cout << "Zle zadany index" << endl;
	}*/

	//vector.at(vector.Length() + 1);

	for (int i = 0; i < 101; i++)
		vector.push_back(5);
	//vector.printData();
	
	Timer::end("\nCas trvania pre Class myVector: ");

	tempSum = 0;

	cout << "Class vector:" << endl;

	Timer::start();
	std::vector<int> vector2(10000000, 1);

	for (int i = 0; i < vector2.capacity(); i++)
		tempSum += vector2.at(i);

	cout << "Suma prvkov vector: " << tempSum << endl;
	
	vector2.resize(20000000);
	cout << "resize done" << endl;

	for (int i = 0; i < 101; i++)
		vector2.push_back(5);

	Timer::end("\nCas trvania pre Class vector: ");
	return 0;
}