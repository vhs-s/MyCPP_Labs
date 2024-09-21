// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

enum class figure_type{square, equilateral_hexagon, equilateral_triangle, circle};

struct figure {
	figure_type type;
	double side;
};

/*
* Создание фигуры.
* 
* return возвращает переменную типа figure с полями тип и сторона.
*/
figure create_figure() {
	figure my_figure;
	my_figure.type = figure_type(0 + rand() % 4);
	my_figure.side = 1 + (rand() %  100) / 10.0;
	return my_figure;
}

/*
* Создание массива фигур.
* 
* @paran N размер массива.
* 
* return возвращает массив фигур.
*/
figure* create_array(int N) {
	figure* my_array_figures = new figure[N];
	srand(time(0));
	for (int i = 0; i < N; i++) {
		my_array_figures[i] = create_figure();
	}
	return my_array_figures;
}

/*
* Обозначение типов фигур строковыми значениями.
* 
* @param type тип фигуры.
* 
* return возвращает строковое значение для соответствующего типа фигуры.
*/
string figure_type_to_string(figure_type type) {
	switch (type) {
	case figure_type::square: return "Квадрат";
	case figure_type::equilateral_hexagon: return "Шестиугольник";
	case figure_type::equilateral_triangle: return "Треугольник";
	case figure_type::circle: return "Круг";
	default: return "Unknown";
	}
}

/*
* Вычисление площади окружности.
* 
* @param side радиус окружности.
* 
* return возвращает значение площади окружности
*/
double circle_area(double side) {
	const double PI = 3.141592653589793;
	return PI * side * side;
}

/*
* Вычисление площади квадрата.
* 
* @param side сторона квадрата.
* 
* return возвращает значение площади квадрата.
*/
double square_area(double side) {
	return side * side;
}

/*
* Вычисление площади шестиугольника.
* 
* @param side сторона шестиугольника.
* 
* return возвращает значение площади шестиугольника.
*/
double hexagon_area(double side) {
	return (3 * sqrt(3) / 2) * side * side;
}

/*
* Вычисление площади треугольника.
* 
* @param side сторона треугольника(равностороннего).
* 
* return возвращает значение площади треугольника.
*/
double triangle_area(double side) {
	return side * side * sqrt(3) / 2;
}

/*
* Вычисление суммарной площади фигур и количества каждого типа фигур.
* 
* @param my_array_figures массив фигур.
* @param N размер массива.
* 
* return возвращает суммарную площадь фигур.
*/
double count_figure_area_and_types(figure* my_array_figures, int N) {
	double S_summary = 0;
	int figure_types[] { 0, 0, 0, 0 };
 	for (int i = 0; i < N; i++) {
		if (figure_type_to_string(my_array_figures[i].type) == "Квадрат") {
			S_summary += square_area(my_array_figures[i].side);
			figure_types[0]++;
		}
		else if (figure_type_to_string(my_array_figures[i].type) == "Шестиугольник") {
			S_summary += hexagon_area(my_array_figures[i].side);
			figure_types[1]++;
		}
		else if (figure_type_to_string(my_array_figures[i].type) == "Треугольник") {
			S_summary += triangle_area(my_array_figures[i].side);
			figure_types[2]++;
		}
		else if (figure_type_to_string(my_array_figures[i].type) == "Круг") {
			S_summary += circle_area(my_array_figures[i].side);
			figure_types[3]++;
		}
	}
	cout << "Количество Квадратов: " << figure_types[0] << "\nКоличество Шестиугольников: " << figure_types[1] << "\nКоличество Треугольников: " << figure_types[2] << "\nКоличество Кругов: " << figure_types[3] << endl;

	return S_summary;
}

/*
* Вывод значений площади фигур, которые больше значения указанного пользователем.
* 
* @param my_array_figures массив фигур.
* @param N размер массива.
* 
*/
static void user_comparison(figure* my_array_figures, int N) {
	double user_square;
	int flag = 0;
	cout << "Введите площадь для сравнения: ";
	cin >> user_square;
	for (int i = 0; i < N; i++) {
		if (figure_type_to_string(my_array_figures[i].type) == "Квадрат") {
			if (square_area(my_array_figures[i].side) > user_square) { cout << "Квадрат со стороной: " << my_array_figures[i].side << " Имеет площадь больше заданной" << endl; flag++; }
		}
		else if (figure_type_to_string(my_array_figures[i].type) == "Шестиугольник") {
			if (hexagon_area(my_array_figures[i].side) > user_square) { cout << "Шестиугольник со стороной: " << my_array_figures[i].side << " Имеет площадь больше заданной" << endl; flag++; }
		}
		else if (figure_type_to_string(my_array_figures[i].type) == "Треугольник") {
			if (triangle_area(my_array_figures[i].side) > user_square) { cout << "Треугольник со стороной: " << my_array_figures[i].side << " Имеет площадь больше заданной" << endl; flag++; }
		}
		else if (figure_type_to_string(my_array_figures[i].type) == "Круг") {
			if (circle_area(my_array_figures[i].side) > user_square) { cout << "Круг со стороной: " << my_array_figures[i].side << " Имеет площадь больше заданной" << endl; flag++; }
		}
	}
	if (flag == 0) {
		cout << "Все площади меньше заданной";
	}

}

/*
* Нахождение радиуса фигуры взависимости от типа.
* 
* @param my_figure фигура.
* 
* return возвращает радиус фигуры.
*/
double find_radius(figure my_figure) {
		if (figure_type_to_string(my_figure.type) == "Квадрат") {
			return my_figure.side / sqrt(2);
		}
		else if (figure_type_to_string(my_figure.type) == "Шестиугольник") {
			return  my_figure.side;
		}
		else if (figure_type_to_string(my_figure.type) == "Треугольник") {
			return  my_figure.side / 2 * sqrt(3);
		}
		else if (figure_type_to_string(my_figure.type) == "Круг") {
			return  my_figure.side;
		}
}

/*
* Поиск минимального радиуса окружности, в которую можно вписать все фигур.
* 
* @param my_array_figures массив фигур.
* @param N размер массива.
*/
void find_minimal_radius(figure* my_array_figures, int N) {
	double minradius = 0;
	for (int i = 0; i < N; i++) {
		if (find_radius(my_array_figures[i]) > minradius) {
			minradius = find_radius(my_array_figures[i]);
		}
	}
	cout << "\nРадиус окружности в которую можно вписать все фигуры: " << minradius << endl;
}

/*
* Вывод массива фигур.
* 
* @param my_array_figures массив фигур.
* @param N размер массива.
*/
void show_my_array(figure* my_array_figures, int N) {
	for (int i = 0; i < N; i++) {
		cout << "\nФигура:" << figure_type_to_string(my_array_figures[i].type) << " со стороной: " << my_array_figures[i].side << " " << endl;
	}
	cout << endl;
}
/*
* Пользовательский ввод.
* 
* return возвращает приведенное к int значение.
*/
int user_input() {
	string user_number;
	cin >> user_number;
	return stoi(user_number);
}
/*
* Точка входа в программу. Запрашивает у пользователя размер массива фигур. Создает массив фигур. Выводит массив фигур. Выводит суммарную площадь фигур. Выводит фигуры, у которых площадь больше заданной пользователем. Находит минимальный радиус окружности, в которую можно вписать все фигуры.
*/
int main()
{
	setlocale(LC_ALL, "RU");
	int exit = 1;
	while (exit != 0) {
		cout << "Введите количество фигур: ";
		int N = user_input();
		figure* my_figures = create_array(N);
		show_my_array(my_figures, N);
		cout << "\nСуммарная площадь всех фигур: " << count_figure_area_and_types(my_figures, N) << endl;
		user_comparison(my_figures, N);
		find_minimal_radius(my_figures, N);
		cout << "Чтобы начать заново введите '1' " << endl;
		exit = user_input();
	}
}

