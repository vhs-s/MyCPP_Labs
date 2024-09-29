// lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <termcolor/termcolor.hpp>
#include <iostream>

using namespace std;

enum class Rarity {
    UNIQUE,
    VINTAGE,
    STRANGE,
    UNUSUAL,
    ORIGINAL
};
/*
* Даёт строковое представление каждой редкости.
* 
* @param rar редкость предмета.
* 
* return возвращает строковое значение редкости предмета.
*/
string rarity_to_string(Rarity rar) {
    switch (rar) {
    case Rarity::UNIQUE: return "UNIQUE";
    case Rarity::VINTAGE: return "VINTAGE";
    case Rarity::STRANGE: return "STRANGE";
    case Rarity::UNUSUAL: return "UNUSUAL";
    case Rarity::ORIGINAL: return "ORIGINAL";
    default: return "Unknown";
    }
}

/*
* Придает описание каждому навыку.
* 
* @param skill_name название навыка.
*/
void add_describe_skills(string skill_name) {
    if (skill_name == "Заговор огня") {
        cout << "\n*Враг, получивший удар, начинает" << termcolor::bright_yellow << " гореть " << termcolor::reset << "некоторое время* " << endl;
    }
    if (skill_name == "Острота") {
        cout << "\n/\\Враг, получивший удар, не может остановить"<< termcolor::bright_red << " кровотечение " << termcolor::reset <<"некоторое время/\\" << endl;
    }
    if (skill_name == "Отбрасывание") {
        cout << "\n-->Врага, получившего" << termcolor::bright_green << " удар, отбрасывает " << termcolor::reset << "на несколько метров-- > " << endl;
    }
    if (skill_name == "Верность") {
        cout << "\n<--->Брошенный" << termcolor::bright_blue << " предмет возвращается " << termcolor::reset << "владельцу<--->" << endl;
    }
    if (skill_name == "Притяжение") {
        cout << "\n>---<" << termcolor::bright_cyan << "Вы следуете прямиком за брошенным предметом" << termcolor::reset << ">---<" << endl;
    }
    if (skill_name == "Удар молнии") {
        cout << "\n/|/При попадании" << termcolor::yellow << " бьёт врага молнией" << termcolor::reset << "/|/" << endl;
    }
    if (skill_name == "Бесконечность") {
        cout << "\n0X0"<< termcolor::bright_magenta<<"Снаряды не тратятся"<< termcolor::reset <<"0X0" << endl;
    }
    if (skill_name == "Горящая стрела") {
        cout << "\n>-->>*Выпущенная" << termcolor::bright_yellow << " стрела будет гореть" << termcolor::reset << ">-- >> *" << endl;
    }
    if (skill_name == "Взрывное попадание") {
        cout << "\n\\* \\* \\*"<<termcolor::green <<"Снаряд,"<<termcolor::reset<<" попавший во врага, "<< termcolor::green<<"взрывается"<<termcolor::reset<<"*/ */ */" << endl;
    }
}

/*
* Красит строковое значение редкости предмета.
* 
* @param rar редкость предмета.
*/
void color_from_rarity(Rarity rar) {
    switch (rar) {
    case Rarity::UNIQUE:
        cout << termcolor::yellow << rarity_to_string(rar) << termcolor::reset << endl;
        break;
    case Rarity::VINTAGE:
        cout << termcolor::blue << rarity_to_string(rar) << termcolor::reset << endl;
        break;
    case Rarity::STRANGE:
        cout << termcolor::green << rarity_to_string(rar) << termcolor::reset << endl;
        break;
    case Rarity::UNUSUAL:
        cout << termcolor::magenta << rarity_to_string(rar) << termcolor::reset << endl;
        break;
    case Rarity::ORIGINAL:
        cout << termcolor::red << rarity_to_string(rar) << termcolor::reset << endl;
        break;
    }

}

class Sword {
    string type = "Sword";
    double damage;
    double durability;
    double attack_speed;
    int skills_quantity;
    string skills_names[3];
    Rarity rar;
public:
    /*
    * Конструктор для типа Sword.
    * 
    * @param rar редкость предмета.
    */
    Sword(Rarity rar) {
        this->damage = calc_damage_from_rarity(rar);
        this->durability = calc_durability_from_rarity(rar);
        this->attack_speed = calc_attack_speed_from_rarity(rar);
        this->rar = rar;
        skills_quantity = 0;
        put_skills_on();
    }

   /*
   * Высчитывает случайное значение урона предмета взависимости от редкости.
   * 
   * @param rar редкость предмета.
   * 
   * return возвращает случайное значение урона предмета.
   */
   double calc_damage_from_rarity(Rarity rar) {
       return 1 + rand() % 20 + static_cast<int>(rar) * 40;
    }
   /*
   * Высчитывает случайное значение прочности предмета взависимости от редкости.
   *
   * @param rar редкость предмета.
   *
   * return возвращает случайное значение прочности предмета.
   */
   double calc_durability_from_rarity(Rarity rar) {
       return 1 + rand() % 100 + static_cast<int>(rar) * 20;
   }
   /*
  * Высчитывает случайное значение скорости атаки предмета взависимости от редкости.
  *
  * @param rar редкость предмета.
  *
  * return возвращает случайное значение скорости атаки предмета.
  */
   double calc_attack_speed_from_rarity(Rarity rar) {
       return 1 + rand() % 50 + static_cast<int>(rar) * 10;
   }
   /*
   * Накладывает навыки/чары взависимости от редкости предмета.
   */
   void put_skills_on() {
       if (rar >= Rarity::STRANGE) {
           skills_names[skills_quantity++] = "Отбрасывание";
       }
       if (rar >= Rarity::UNUSUAL) {
           skills_names[skills_quantity++] = "Острота";
       }
       if (rar >= Rarity::ORIGINAL) {
           skills_names[skills_quantity++] = "Заговор огня";
       }
   }
   /*
   * Выводит в консоль характеристики предмета.
   */
   void display() {
       cout << "Оружие: " << type << endl;
       cout << "Урон: " << damage << ", Прочность: " << durability
           << ", Скорость атаки: " << attack_speed << ", Редкость: "; color_from_rarity(rar);
       cout << termcolor::cyan << "Наложенные чары/навыки\n" << termcolor::reset;
       for (int i = 0; i < skills_quantity; i++) {
           cout << "\n" << skills_names[i] << " ";
           add_describe_skills(skills_names[i]);
       }
   }
};


class Spear {
    string type;
    double damage;
    double durability;
    double attack_speed;
    int skills_quantity;
    string skills_names[3];
    Rarity rar;
public:
    /*
    * Конструктор для типа Spear.
    * 
    * @param rar.
    */
    Spear(Rarity rar) {
        this->type = "Spear";
        this->damage = calc_damage_from_rarity(rar);
        this->durability = calc_durability_from_rarity(rar);
        this->attack_speed = calc_attack_speed_from_rarity(rar);
        this->rar = rar;
        skills_quantity = 0;
        put_skills_on();
    }
     /*
   * Высчитывает случайное значение урона предмета взависимости от редкости.
   *
   * @param rar редкость предмета.
   *
   * return возвращает случайное значение урона предмета.
   */
    double calc_damage_from_rarity(Rarity rar) {
        return 1 + rand() % 10 + static_cast<int>(rar) * 20;
    }
    /*
  * Высчитывает случайное значение прочности предмета взависимости от редкости.
  *
  * @param rar редкость предмета.
  *
  * return возвращает случайное значение прочности предмета.
  */
    double calc_durability_from_rarity(Rarity rar) {
        return 1 + rand() % 50 + static_cast<int>(rar) * 10;
    }
    /*
  * Высчитывает случайное значение скорости атаки предмета взависимости от редкости.
  *
  * @param rar редкость предмета.
  *
  * return возвращает случайное значение скорости атаки предмета.
  */
    double calc_attack_speed_from_rarity(Rarity rar) {
        return 1 + rand() % 25 + static_cast<int>(rar) * 15;
    }
    /*
   * Накладывает навыки/чары взависимости от редкости предмета.
   */
    void put_skills_on() {
        if (rar >= Rarity::STRANGE) {
            skills_names[skills_quantity++] = "Верность";
        }
        if (rar >= Rarity::UNUSUAL) {
            skills_names[skills_quantity++] = "Притяжение";
        }
        if (rar >= Rarity::ORIGINAL) {
            skills_names[skills_quantity++] = "Удар молнии";
        }
    }
    /*
  * Выводит в консоль характеристики предмета.
  */
    void display() {
        cout << "Оружие: " << type << endl;
        cout << "Урон: " << damage << ", Прочность: " << durability
            << ", Скорость атаки: " << attack_speed << ", Редкость: "; color_from_rarity(rar);
        cout << termcolor::cyan << "Наложенные чары/навыки\n" << termcolor::reset;
        for (int i = 0; i < skills_quantity; i++) {
            cout << "\n" << skills_names[i] << " ";
            add_describe_skills(skills_names[i]);
        }
    }
};

class Bow {
    string type;
    double damage;
    double durability;
    double attack_speed;
    int skills_quantity;
    string skills_names[3];
    Rarity rar;
public:
    /*
   * Конструктор для типа Bow.
   *
   * @param rar.
   */
    Bow(Rarity rar) {
        this->type = "Bow";
        this->damage = calc_damage_from_rarity(rar);
        this->durability = calc_durability_from_rarity(rar);
        this->attack_speed = calc_attack_speed_from_rarity(rar);
        this->rar = rar;
        skills_quantity = 0;
        put_skills_on();
    }
      /*
   * Высчитывает случайное значение урона предмета взависимости от редкости.
   *
   * @param rar редкость предмета.
   *
   * return возвращает случайное значение урона предмета.
   */
    double calc_damage_from_rarity(Rarity rar) {
        return 1 + rand() % 30 + static_cast<int>(rar) * 30;
    }
      /*
   * Высчитывает случайное значение прочности предмета взависимости от редкости.
   *
   * @param rar редкость предмета.
   *
   * return возвращает случайное значение прочности предмета.
   */
    double calc_durability_from_rarity(Rarity rar) {
        return 1 + rand() % 70 + static_cast<int>(rar) * 15;
    }
      /*
   * Высчитывает случайное значение скорости атаки предмета взависимости от редкости.
   *
   * @param rar редкость предмета.
   *
   * return возвращает случайное значение скорости атаки предмета.
   */
    double calc_attack_speed_from_rarity(Rarity rar) {
        return 1 + rand() % 75 + static_cast<int>(rar) * 30;
    }
      /*
   * Накладывает навыки/чары взависимости от редкости предмета.
   */
    void put_skills_on() {
        if (rar >= Rarity::STRANGE) {
            skills_names[skills_quantity++] = "Бесконечность";
        }
        if (rar >= Rarity::UNUSUAL) {
            skills_names[skills_quantity++] = "Горящая стрела";
        }
        if (rar >= Rarity::ORIGINAL) {
            skills_names[skills_quantity++] = "Взрывное попадание";
        }
    }
    /*
  * Выводит в консоль характеристики предмета.
  */
    void display() {
            cout << "Оружие: " << type << endl; 
            cout << "Урон: " << damage << ", Прочность: " << durability
                << ", Скорость атаки: " << attack_speed << ", Редкость: "; color_from_rarity(rar);
            cout << termcolor::cyan << "Наложенные чары/навыки\n" << termcolor::reset;
        for (int i = 0; i < skills_quantity; i++) {
            cout << "\n" << skills_names[i] << " ";
            add_describe_skills(skills_names[i]);
        }
    }
};

class Weapon {

public:
    void* weapon;
    string type;
    Rarity rar;
    /*
    * Конструктор для типа Weapon.
    * 
    * @param weapon указатель на пустоту для будщего типа предмета(Sword, Spear, Bow).
    * @param type вид оружия.
    * @param rar редкость предмета.
    */
    Weapon(void* weapon, string type, Rarity rar) {
        this->weapon = weapon;
        this->type = type;
        this->rar = rar;
    }
    /*
    * Выводит характеристики оружия взависимости от вида.
    */
    void display() {
        if (type == "Sword") {
            Sword* sword = static_cast<Sword*>(weapon);
            sword->display();
        }
        else if (type == "Spear") {
            Spear* spear = static_cast<Spear*>(weapon);
            spear->display();
        }
        else if (type == "Bow") {
            Bow* bow = static_cast<Bow*>(weapon);
            bow->display();
        }
    }
};

class Shop {
    Weapon* lots[100];
    int lots_quantity;
public:
    /*
    * Конструктор для типа Shop.
    */
    Shop() {
        lots_quantity = 0;
        filling_Shop();
    }

    /*
    * Заполняет магазин предметами в количестве соответстующих их редкости.
    */
    void filling_Shop() {
        filling_weapons_for_rarity(Rarity::UNIQUE, 5); 
        filling_weapons_for_rarity(Rarity::VINTAGE, 4);
        filling_weapons_for_rarity(Rarity::STRANGE, 3);
        filling_weapons_for_rarity(Rarity::UNUSUAL, 2);
        filling_weapons_for_rarity(Rarity::ORIGINAL, 1);
    }
    /*
    * Заполняет магазин предметами в количестве соответстующих их редкости.
    * 
    * @param rar редкость предмета.
    * @param count количество наборов(В одном наборе три предмета разных).
    */
    void filling_weapons_for_rarity(Rarity rar, int count) {
        string weapon_types[] = { "Sword", "Spear", "Bow" }; 

        for (int i = 0; i < count; ++i) {  
            for (string type : weapon_types) { 
                filling_random_weapon(rar, type);
            }
        }
    }
    /*
    * Заполняет массив предметов оружиями заданного типа и редкости.
    * 
    * @param rar редкость предмета.
    * @param type вид оружия.
    */
    void  filling_random_weapon(Rarity rar, string type) {
        if (type == "Sword") {
            lots[lots_quantity++] = new Weapon(new Sword(rar), "Sword", rar);
        }
        else if (type == "Spear") {
            lots[lots_quantity++] = new Weapon(new Spear(rar), "Spear", rar);
        }
        else if (type == "Bow") {
            lots[lots_quantity++] = new Weapon(new Bow(rar), "Bow", rar);
        }
    }
    /*
    * Выводит список предметов определенного вида в магазине по выбору пользователя.
    */
    void user_choice_type_weapon(Weapon* lot, int user_choice, string type) {
        if (user_choice == 1 && lot->type == "Sword") {
            lot->display ();
            cout << termcolor::bright_white << "\n+--------------------+\n" << termcolor::reset;
        }
        if (user_choice == 2 && lot->type == "Spear") {
            lot->display();
            cout << termcolor::bright_white << "\n+--------------------+\n" << termcolor::reset;
        }
        if (user_choice == 3 && lot->type == "Bow") {
            lot->display();
            cout << termcolor::bright_white << "\n+--------------------+\n" << termcolor::reset;
        }
    }
    /*
    * Выводит список предметов в магазине  в зависимости от ценового диапазона, который выберет пользователь.
    */
    void display_items() {
        int user_capital;
        int user_choice;
        for (;;) {
            cout << "Какой вид оружия Вас интересует?"<<termcolor::bright_green<<"\n3 - Лук"<<termcolor::bright_blue<<"\n2 - Копьё"<<termcolor::bright_red<<"\n1 - Меч"<<termcolor::reset<< endl;
            cin >> user_choice;
            cout << "В каком ценовом диапазоне планируете покупку?"<<termcolor::magenta<<"\n3 - Премиум варианты"<<termcolor::bright_blue<<"\n2 - Среднего уровня"<<termcolor::green<<"\n1 - Экономичные варианты"<<termcolor::reset<<"\n0 - Выход из магазина" << endl;
            cin >> user_capital;

            system("cls");
            for (int i = 0; i < lots_quantity; i++) {
                switch (user_capital)
                {
                case 1:
                    if (lots[i]->rar <= Rarity::VINTAGE) {
                        user_choice_type_weapon(lots[i], user_choice, lots[i]->type);
                    }
                    break;
                case 2:
                    if (lots[i]->rar >= Rarity::STRANGE && lots[i]->rar <= Rarity::UNUSUAL) {
                        user_choice_type_weapon(lots[i], user_choice, lots[i]->type);
                    }
                    break;
                case 3:
                    if (lots[i]->rar == Rarity::ORIGINAL) {
                        user_choice_type_weapon(lots[i], user_choice, lots[i]->type);
                    }
                    break;
                default:
                    goto loop;
                }
            }
       
        }
    loop:
        return;
    }

};
   
/*
* Точка входа в программу. Спрашивает у пользователя желание зайти в магазин, в случае положительного ответа предоставляет список оружий определенной редкости и ценового диапазона по выбору пользователя.
*/
int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int user_choice;
    for (;;) {
        cout << "Зайти в магазин?\n1 - Да\n0 - Нет" << endl;
        cin >> user_choice;
        if (user_choice == 0) {
            break;
        }
        Shop shop;
        shop.display_items();
    }

}
