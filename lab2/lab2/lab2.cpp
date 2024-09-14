// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include<ctime>
using namespace std;

/*
* Заполнение массива разамера N случайными чилсами от 0 до 20.
* 
* @param N размер массива.
* 
* return возвращает массив размера N заполненный случайными числами от 0 до 20.
*/

int* rand_flow_array(int N) {
	int* my_array_numbers = new int[N];
	srand(time(0));
	for (int i = 0; i < N; i++) {
		my_array_numbers[i] = 0 + rand() % 21;
	}
	return my_array_numbers;
}

/*
* Вывод массива размера N в консоль.
* 
* @param my_array_numbers массив, элементы которого нужно вывести в консоль.
* @param N размер массива.
* 
*/

void show_my_array(int* my_array_numbers, int N) {
	for (int i = 0; i < N; i++) {
		cout << my_array_numbers[i] << " ";
	}
	cout << endl;
}

/*
* Ввод пользователем целого числа.
* 
* return возвращает ввёденное пользователем целое число. 
*/
int user_input() {
	string user_number;
	cin >> user_number;
	return stoi(user_number);
}		

/*
* Создание среза массива.
* 
* @param my_array_numbers массив, по которому нужно выполнить срез.
* @param start левая граница среза.
* @param end правая граница среза.
*/

void slice(int* my_array_numbers, int start, int end) {
	int* slicedArray = new int[end - start];

	for (int i = 0; i < end; i++) {
		slicedArray[i] = my_array_numbers[start + i];
	}
	show_my_array(slicedArray, end - start);

}

/*
* Поиск возрастающих последовательностей в массиве размера N.
* 
* @param my_array_numbers массив, в котором нужно найти возрастающие последовательности.
* @param N размер массива.
*/

void find_increasing_subseq(int* my_array_numbers, int N) {
	int* finded_subsequences = new int[N];
	int j = 0;
	int subsequence_count = 0;

	for (int i = 0; i < N - 1; i++) {
		if (my_array_numbers[i] < my_array_numbers[i + 1]) {
			finded_subsequences[j++] = my_array_numbers[i];
		}
		else {
			if (j >= 2) {
				finded_subsequences[j++] = my_array_numbers[i];
				cout << "Найдена возрастающая последовательность #" << subsequence_count++ << ": ";
				for (int p = 0; p < j; p++) {
					cout << finded_subsequences[p] << " ";
				}
				cout << endl;
			}
			j = 0;
		}
	}

	if (j >= 2) {
		finded_subsequences[j++] = my_array_numbers[N - 1];
		cout << "Найдена возрастающая последовательность #" << subsequence_count++ << ": ";
		for (int p = 0; p < j; p++) {
			cout << finded_subsequences[p] << " ";
		}
		cout << endl;
	}
}

/*
* Поиск убывающих последовательностей в массиве размера N.
*
* @param my_array_numbers массив, в котором нужно найти убывающие последовательности.
* @param N размер массива.
*/

void find_decreasing_subseq(int* my_array_numbers, int N) {
	int* finded_subsequences = new int[N];
	int j = 0;
	int subsequence_count = 0;

	for (int i = 0; i < N - 1; i++) {
		if (my_array_numbers[i] > my_array_numbers[i + 1]) {
			finded_subsequences[j++] = my_array_numbers[i];
		}
		else {
			if (j >= 2) {
				finded_subsequences[j++] = my_array_numbers[i];
				cout << "Найдена убывающая последовательность #" << subsequence_count++ << ": ";
				for (int p = 0; p < j; p++) {
					cout << finded_subsequences[p] << " ";
				}
				cout << endl;
			}
			j = 0;
		}
	}

	if (j >= 2) {
		finded_subsequences[j++] = my_array_numbers[N - 1];
		cout << "Найдена убывающая последовательность #" << subsequence_count++ << ": ";
		for (int p = 0; p < j; p++) {
			cout << finded_subsequences[p] << " ";
		}
		cout << endl;
	}
}

/*
* Поиск чередующихся последовательностей в массиве размера N.
*
* @param my_array_numbers массив, в котором нужно найти чередующиеся последовательности.
* @param N размер массива.
*/

void find_alternating_subseq(int* my_array_numbers, int N) {
	int* finded_subsequences = new int[N];  
	int j = 0;  
	int subsequence_count = 0;  

	for (int i = 0; i < N - 2; i++) {
		
		if (j == 0) {
			finded_subsequences[j++] = my_array_numbers[i];
		}

		if ((my_array_numbers[i] < my_array_numbers[i + 1] && my_array_numbers[i + 1] > my_array_numbers[i + 2]) ||
			(my_array_numbers[i] > my_array_numbers[i + 1] && my_array_numbers[i + 1] < my_array_numbers[i + 2])) {

			finded_subsequences[j++] = my_array_numbers[i + 1]; 
		}
		else {
			finded_subsequences[j++] = my_array_numbers[i + 1];

			if (j >= 3) {
				cout << "Найдена чередующаяся последовательность #" << subsequence_count++ << ": ";
				for (int p = 0; p < j; p++) {
					cout << finded_subsequences[p] << " ";
				}
				cout << endl;
			}
			j = 0;
		}
	}

	if (j >= 3) {
		cout << "Найдена чередующаяся последовательность #" << subsequence_count++ << ": ";
		for (int p = 0; p < j; p++) {
			cout << finded_subsequences[p] << " ";
		}
		cout << endl;
	}
}

/*
* Поиск последовательностей в массиве;
* 
* @param my_array_numbers массив, в котором нужно найти последовательности.
* @param N размер массива.
* 
* return возвращает 0 для успешного выхода из функции.
*/

int subsequence_find(int* my_array_numbers, int N) {
	for (;;) {
		cout << "1: Поиск возрастающих последовательностей\n\
2: Поиск убывающих последовательностей\n\
3: Поиск чередующихся последовательностей\n\
4: Выход\n" << endl;
		switch (user_input())
		{
		case 1:
			find_increasing_subseq(my_array_numbers, N);
			break;
		case 2:
			find_decreasing_subseq(my_array_numbers, N);
			break;
		case 3:
			find_alternating_subseq(my_array_numbers, N);
			break;
		default:
			goto loop;
		}
	}
loop:
	return 0;
}

/*
* Сортирует массив в порядке возрастания, при помощи сортировки вставками.
* 
* @param my_array_numbers массив, который нужно отсортировать.
* @param N размер массива.
*/

void insert_sort(int* my_array_numbers, int N) {
	int key;
	int j;
	for (int i = 1; i < N; i++) {
		key = my_array_numbers[i];
		j = i - 1;
		while (j >= 0 && my_array_numbers[j] > key) {
			my_array_numbers[j + 1] = my_array_numbers[j];
			j--;
		}
		my_array_numbers[j + 1] = key;
	}
	cout << "Отсортированный массив" << endl;
	show_my_array(my_array_numbers, N);

}

/*
* Нахожденмие минимума и максимума, среднего арифметического, медианного значений в массиве.
* 
* @param my_array_numbers массив, в котором выполняется поиск.
* @param N размер массива.
*/

void find_min_max_med_middle(int* my_array_numbers, int N) {
	int pack_of_meaning[] = { 0, 0, my_array_numbers[0], 0};
	int sum = 0;
	double med;
	for (int i = 0; i < N; i++) {
		if (my_array_numbers[i] > pack_of_meaning[0]) {
			pack_of_meaning[0] = my_array_numbers[i];
			pack_of_meaning[1] = i;
		}
	}
	for (int i = 0; i < N; i++) {
		if (my_array_numbers[i] < pack_of_meaning[2]) {
			pack_of_meaning[2] = my_array_numbers[i];
			pack_of_meaning[3] = i;
		}
	}
	for (int i = 0; i < N; i++) {
		sum += my_array_numbers[i];
	}
	insert_sort(my_array_numbers, N);
	if (N % 2 == 0) {
		med = (double(my_array_numbers[N / 2 - 1]) + double(my_array_numbers[N / 2])) / 2;
	}
	else {
		int index = N / 2;
		med = (my_array_numbers[index]);
	}
	cout << "Максимальный элемент (исходный массив): " << pack_of_meaning[0] << ", с индексом: " << pack_of_meaning[1]<<
		"\n\nМинимальный элемент (исходный массив): " << pack_of_meaning[2] << ", с индексом " << pack_of_meaning[3]<<
		"\n\nСреднее арифметическое: " << double(sum)/N << "\n\nМедианное значение (отсортированный массив): " << med << endl;
}

/*
* Выводит меню для пользователя в консоль.
*/

void get_menu() {
	cout << "1: Поиск последовательностей(убывающей, возрастающей, чередующейся)\n\
2: Поиск максимального и минимального значения в массиве, с указанием их индекса, среднего арифметического и медианного значений среди всех элементов массива.\n\
3: Формирование среза массива от введенного номера элемента a и до введенного номера элемента b.\n\
4: Сортировка массива при помощи сортировки вставками\n\
5: Выход" << endl;
}

/*
* Точка входа в программу после задания массива предлагает одно из пяти дейсвий.
*/
int main()
{
	setlocale(LC_ALL, "RU");
	for (;;) {
		cout << "Введите размер массива для заполнения: ";
		int N = user_input();
		int start, end;
		get_menu();
		int* sequence = new int[N];
		sequence = rand_flow_array(N);
		show_my_array(sequence, N);
		switch (user_input()) {
			case 1:
				subsequence_find(sequence, N);
				break;
			case 2:
				find_min_max_med_middle(sequence, N);
				break;
			case 3:
				cout << "Введите a: " << endl;
				start = user_input();
				cout << "Введите b: " << endl;
				end = user_input();
				slice(sequence, start, end);
				break;
			case 4:
				insert_sort(sequence, N);
				break;
			default:
				goto loop;
		}
	}
loop:
	return 0;
}


