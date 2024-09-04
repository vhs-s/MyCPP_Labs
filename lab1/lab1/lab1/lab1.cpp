// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
* Создание и заполнение вектора числами от 0 до предела N
* 
* @param N предел заполнения числами (задаётся пользователем)
* @return возвращает заполненный вектор числами от 0 до N
*/
vector<int> new_vector_of_numbers(int N) {
	vector<int> newVector;
	for (int i = 0; i <= N; i++){
		newVector.push_back(i);
	}
	return newVector;
}

/*
* Вывод всех значений вектора в консоль
* 
* @param myVector вектор, значения которого нужно вывести
*/
void list_show(vector<int> myVector) {
	for (int num : myVector) {
		cout << num << " ";
	}
	cout << endl;
}
/*
* Обработчик ввода пользователя
* 
* @return возвращает явно преобразованную к int строку, которую ввёл пользователь
*/
int user_input() {
	cout << "Введите верхний предел для поиска простых чисел: ";
	string user_number;
	cin >> user_number;
	return stoi(user_number);
}


/*
* Поиск простых чисел при помощи алгоритма Решето Эратосфена
* 
* @param myVector вектор содержащий исходную последовательность чисел
* 
* return возвращает вектор содержащий простые числа, найденные из последовательности
* 
* Пример:
*		Исходная последовательность: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
*		Найденные простые числа: 2, 3, 5, 7
*/
vector<int> sieve_of_eratosthenes(vector<int> myVector) {
	vector<int> prime_vector;
	myVector[0] = myVector[1] = 0;
	for (int j = 2; j < myVector.size(); j++) {
		if (myVector[j] != 0) {
			prime_vector.push_back(myVector[j]);
			for (int i = j * j; i < myVector.size(); i += j) {
				myVector[i] = 0;
			}
		}

	}

	return prime_vector;

}

/*
* Точка входа программы
* 
* Запрашивает у пользователя верхний предел для формирования последовательности
* Выводит исходную последовательность
* По алгоритму Решето Эратосфена находит простые числа из заданной последовательности
* Выводит найденные простые числа
*/
int main()
{
	setlocale(LC_ALL, "RU");
	vector<int> myVector = new_vector_of_numbers(user_input());
	vector<int> newVector;
	cout << "Исходный ряд:" << endl;
	list_show(myVector);
	newVector = sieve_of_eratosthenes(myVector);
	cout << "Найденные простые числа:" << endl;
	list_show(newVector);
}


