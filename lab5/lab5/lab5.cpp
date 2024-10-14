#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SPELLS = 20;
const int MAX_MAGES = 20;
const int MAX_ROUNDS = 10;

class Spell {
public:
    int manaCost;
    int difficulty;
    int castDuration;  
    int range;        
    int effectDuration; 
    bool isMass;      
    string effect;     
    string name;     
    /*
    * Стандартный конструктор класса Spell.
    */
    Spell() : manaCost(0), difficulty(0), castDuration(0), range(0), effectDuration(0), isMass(false), effect(""), name("") {}
    /*
    * Конструктор для класса Spell
    * 
    * @param name название заклинания
    * @param manaCost стоимость заклинания
    * @param difficulty сложность заклинания
    * @param castDuration время исполнения заклинания
    * @param range дальность заклинания
    * @param effectDuration длительность эффекта в раундах
    * @param isMass является ли оно массовым
    * @param effect название эффекта
    */
    void setSpell(string name, int manaCost, int difficulty, int castDuration, int range, int effectDuration, bool isMass, string effect) {
        this->name = name;
        this->manaCost = manaCost;
        this->difficulty = difficulty;
        this->castDuration = castDuration;
        this->range = range;
        this->effectDuration = effectDuration;
        this->isMass = isMass;
        this->effect = effect;
    }
    /*
    * Метод для вывода в консоль информации о примененном заклинании.
    */
    void apply() const {
        cout << "Применено заклинание: " << name << " с эффектом: " << effect << endl;
    }
    /*
    * Дружественная функция для перегрузки оператора вывода.
    * 
    * @param os поток вывода
    * @param spell объект типа Spell
    * 
    * return возвращает ссылку на поток вывода
    */
    friend ostream& operator<<(ostream& os, const Spell& spell) {
        os << spell.name << " { Mana Cost: " << spell.manaCost
            << ", Difficulty: " << spell.difficulty
            << ", Cast Duration: " << spell.castDuration << "s"
            << ", Range: " << spell.range
            << ", Effect Duration: " << spell.effectDuration << " rounds"
            << ", Mass: " << (spell.isMass ? "Yes" : "No")
            << ", Effect: " << spell.effect << " }";
        return os;
    }
};

class RangedSpell : public Spell {
public:
    /*
    * Конструктор для дальнобойного заклинания
    */
    RangedSpell() {
        string names[] = { "Огненная стрела", "Ледяная игла", "Вихрь" };
        string effects[] = { "Горение", "Замедление", "Дезориентация" };
        int index = rand() % 3;
        setSpell(names[index], rand() % 100 + 1, rand() % 10 + 1, rand() % 3600 + 1, rand() % 50 + 51, rand() % 10 + 1, index == 2, effects[index]);
    }
};

class MeleeSpell : public Spell {
public:
    /*
    * Конструктор для ближнего заклинания
    */
    MeleeSpell() {
        string names[] = { "Удар молнии", "Клинок ветра", "Шоковый удар" };
        string effects[] = { "Оглушение", "Кровотечение", "Паралич" };
        int index = rand() % 3;
        setSpell(names[index], rand() % 100 + 1, rand() % 10 + 1, rand() % 3600 + 1, rand() % 10, rand() % 10 + 1, false, effects[index]);
    }
};

class CurseSpell : public Spell {
public:
    /*
    * Конструктор для заклинания проклятия
    */
    CurseSpell() {
        string names[] = { "Тень смерти", "Проклятие слабости", "Порча" };
        string effects[] = { "Снижение щита", "Замедление", "Порча" };
        int index = rand() % 3;
        setSpell(names[index], rand() % 100 + 1, rand() % 10 + 1, rand() % 3600 + 1, rand() % 50, rand() % 10 + 1, false, effects[index]);
    }
};

class SupportSpell : public Spell {
public:
    /*
    * Конструктор поддерживающего заклинания
    */
    SupportSpell() {
        string names[] = { "Исцеление", "Защитный барьер", "Укрепление" };
        string effects[] = { "Увеличение щита", "Снятие проклятия", "Укрепление" };
        int index = rand() % 3;
        setSpell(names[index], rand() % 100 + 1, rand() % 10 + 1, rand() % 3600 + 1, rand() % 50, rand() % 10 + 1, false, effects[index]);
    }
};

class Mage {
public:
    string name;
    int shield;
    Spell spellHistory[MAX_SPELLS]; 
    Spell spellsAppliedOnMe[MAX_SPELLS];
    int spellCount;                  
    int historyCount;               
    int appliedCount;             
    Spell spells[MAX_SPELLS];   
    /*
    * Стандартный конструктор для класса Mage
    */
    Mage() : shield(100), spellCount(0), historyCount(0), appliedCount(0) {}
    /*
    * Метод для задания имени мага в команде
    * 
    * @param name имя мага.
    */
    void setName(const string& name) {
        this->name = name;
    }
    /*
    * Метод для заполнения массива доступными заклинаниями
    * 
    * @param spell объект типа Spell
    */
    void addSpell(const Spell& spell) {
        if (spellCount < MAX_SPELLS) {
            spells[spellCount++] = spell;
        }
    }
    /*
    * Метод применения заклинания на мага
    * 
    * @param spell объект класса Spell
    * @param target ссылка на конкретного мага из команды
    */
    void applySpell(const Spell& spell, Mage& target) {
        if (historyCount < MAX_SPELLS) {
            spellHistory[historyCount++] = spell; 
            cout << name << " применил заклинание: " << spell.name << " на " << target.name << " с эффектом: " << spell.effect << endl;

            if (spell.effect == "Снижение щита") {
                target.shield -= spell.effectDuration * 10; 
            }
            else if (spell.effect == "Увеличение щита") {
                target.shield += spell.effectDuration * 5;
            }
            else if (spell.effect == "Горение") {
                target.shield -= spell.effectDuration * 5;
            }
            else if (spell.effect == "Оглушение") {
                target.shield -= spell.effectDuration * 6; 
            }

            target.spellsAppliedOnMe[target.appliedCount++] = spell;

            if (target.shield < 0) target.shield = 0;

            spell.apply();

            cout << target.name << " теперь имеет щит: " << target.shield << endl;
        }
    }
    /*
    * Метод для ведения отчетности по магам
    */
    void report() const {
        cout << "Отчет по магу " << name << ":" << endl;
        cout << "Оставшийся щит: " << shield << endl;
        cout << "История примененных заклинаний:" << endl;
        for (int i = 0; i < historyCount; i++) {
            cout << spellHistory[i] << endl; 
        }
        cout << "Заклинания, примененные на меня:" << endl;
        for (int i = 0; i < appliedCount; i++) {
            cout << spellsAppliedOnMe[i] << endl; 
        }
    }
};

class Training {
public:
    Mage team1[MAX_MAGES / 2];
    Mage team2[MAX_MAGES / 2];
    int teamSize;             
    int rounds;               

    /*
    * Конструктор класса Training
    * 
    * @param teamSize количество магов в команде
    * @param rounds количество раундов в тренировке
    */
    Training(int teamSize, int rounds) : teamSize(teamSize), rounds(rounds) {
        for (int i = 0; i < teamSize; i++) {
            team1[i].setName("Маг из первой команды с номером-" + to_string(i + 1));
            team2[i].setName("Маг из второй команды с номером-" + to_string(i + 1));

            team1[i].addSpell(RangedSpell()); 
            team1[i].addSpell(CurseSpell());   
            team2[i].addSpell(MeleeSpell());   
            team2[i].addSpell(SupportSpell()); 
        }
    }
    /*
    * Запуск программы тренировки магов.
    */
    void runTraining() {
        for (int round = 0; round < rounds; ++round) {
            cout << "\nРаунд " << (round + 1) << ":\n";
            for (int i = 0; i < teamSize; ++i) {
                Spell spell1 = team1[i].spells[rand() % 2];
                Spell spell2 = team2[i].spells[rand() % 2];

                if (spell1.effect == "Увеличение щита" || spell1.effect == "Исцеление" || spell1.effect == "Снятие проклятия") {
                    team1[i].applySpell(spell1, team1[i]);
                }
                else {
                    team1[i].applySpell(spell1, team2[i]); 
                }

                if (spell2.effect == "Увеличение щита" || spell2.effect == "Исцеление" || spell2.effect == "Снятие проклятия") {
                    team2[i].applySpell(spell2, team2[i]); 
                }
                else {
                    team2[i].applySpell(spell2, team1[i]); 
                }
            }
        }
    }
    /*
    * Метод для создания общего отчета по тренировке.
    */
    void generateReport() const {
        cout << "\nИтоговый отчет:" << endl;
        for (int i = 0; i < teamSize; ++i) {
            team1[i].report();
            team2[i].report();
        }
    }
};

/*
* Точка входа в программу. Запускает тренировку магов и выводит отчет по тренировке.
*/
int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int stop = 1;
    int userRounds = 0;
    int userMages = 0;
    while (stop != 0) {
        cout << "Начать тренировку (1) или выйти (0)?" << endl;
        cin >> stop;
        if (stop != 0) {
            system("cls");
            cout << "Какое количество раундов будет (до 10)?" << endl;
            cin >> userRounds;
            system("cls");
            cout << "Сколько магов будет в каждой команде (до 10)?" << endl;
            cin >> userMages;
            system("cls");
            Training training(userMages, userRounds);
            training.runTraining();
            training.generateReport();
        }
        else {

        }
    }
    return 0;
}
