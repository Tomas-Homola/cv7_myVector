#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <utility>

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
	T& operator [](int index);
	void push_back(T newValue);
	T& begin() { return data[0]; }
	T& end() { return data[length - 1]; }
	void clear();

	void printData();
};

template<class T>
myVector<T>::myVector(int length, T defaultValue)
{
	this->length = length;
	data = new T[length];

	for (int i = 0; i < this->length, i++)
		data[i] = defaultValue;
}

template<class T>
void myVector<T>::resize(int newLength)
{
	T* newData = new T[newLength];


}

template<class T>
T& myVector<T>::at(int index)
{
	// TODO: insert return statement here
}

template<class T>
T& myVector<T>::operator[](int index)
{
	// TODO: insert return statement here
}

template<class T>
void myVector<T>::push_back(T newValue)
{
}

template<class T>
void myVector<T>::clear()
{
}

template<class T>
void myVector<T>::printData()
{
}
