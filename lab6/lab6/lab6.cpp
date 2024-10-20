#include <iostream>
#include <cmath>
#include <cstdlib>  
#include <ctime>    

/**
 * Базовый класс мишени
 */
class Target {
protected:
    double visibility; // Рассчитанная видимость мишени
    int maxHits;       // Максимальное количество попаданий до разрушения
    int currentHits;   // Текущее количество попаданий
public:

    /**
     * Конструктор класса Target
     * @param maxHits Максимальное количество попаданий до разрушения
     */
    Target(int maxHits) : maxHits(maxHits), currentHits(0) {}

    /**
     * Рассчитывает шанс попадания по мишени
     * @return Рассчитанное значение видимости мишени
     */
    virtual double calculateHitChance() const {
        return visibility;
    }

    /**
     * Обновляет количество попаданий по мишени
     * @param hits Количество нанесённых попаданий
     */
    virtual void takeDamage(int hits) {
        currentHits += hits;
        if (currentHits > maxHits) currentHits = maxHits;
    }

    /**
     * Проверяет, разрушена ли мишень
     * @return Возвращает true, если мишень разрушена, иначе false
     */
    virtual bool isDestroyed() const {
        return currentHits >= maxHits;
    }

    /**
     * Получает текущее количество попаданий по мишени
     * @return Текущее количество попаданий
     */
    int getCurrentHits() const {
        return currentHits;
    }

    /**
     * Получает максимальное количество попаданий для мишени
     * @return Максимальное количество попаданий
     */
    int getMaxHits() const {
        return maxHits;
    }

    /**
     * Получает рассчитанную видимость мишени
     * @return Значение видимости мишени
     */
    double getVisibility() const {
        return visibility;
    }

    /**
     * Перегрузка оператора вывода информации о мишени
     * @param os Ссылка на поток вывода
     * @param target Ссылка на объект мишени
     * @return Ссылка на поток вывода с информацией о мишени
     */
    friend std::ostream& operator<<(std::ostream& os, const Target& target) {
        os << "Target { Visibility: " << target.visibility << ", Max Hits: "
            << target.maxHits << ", Current Hits: " << target.currentHits << " }";
        return os;
    }
};

/**
 * Класс круглой мишени, наследующий Target
 */
class CircularTarget : public Target {
    double radius;     // Радиус круга
    double distance;   // Расстояние до мишени
    bool reflective;   // Мишень отражает свет
public:
    /**
     * Конструктор круглой мишени
     * @param radius Радиус круга
     * @param distance Расстояние до мишени
     * @param reflective Отражает ли мишень свет
     * @param maxHits Максимальное количество попаданий до разрушения
     */
    CircularTarget(double radius, double distance, bool reflective, int maxHits)
        : Target(maxHits), radius(radius), distance(distance), reflective(reflective) {
        visibility = std::min(1.0, (radius / distance) + (reflective ? 0.1 : 0.0));
    }

    /**
     * Рассчитывает шанс попадания по круглой мишени
     * @return Рассчитанное значение видимости
     */
    double calculateHitChance() const override {
        return visibility;
    }
};

/**
 * Класс квадратной мишени, наследующий Target
 */
class SquareTarget : public Target {
    double side;       // Сторона квадрата
    double distance;   // Расстояние до мишени
    bool reflective;   // Мишень отражает свет
public:
    /**
     * Конструктор квадратной мишени
     * @param side Длина стороны квадрата
     * @param distance Расстояние до мишени
     * @param reflective Отражает ли мишень свет
     * @param maxHits Максимальное количество попаданий до разрушения
     */
    SquareTarget(double side, double distance, bool reflective, int maxHits)
        : Target(maxHits), side(side), distance(distance), reflective(reflective) {
        visibility = std::min(1.0, 0.1 + (side / distance) + (reflective ? 0.1 : 0.0));
    }

    /**
     * Рассчитывает шанс попадания по квадратной мишени
     * @return Рассчитанное значение видимости
     */
    double calculateHitChance() const override {
        return visibility;
    }
};

/**
 * Генерирует случайное число от 0 до 1
 * @return Случайное число в диапазоне от 0 до 1
 */
double getRandomDouble() {
    return static_cast<double>(rand()) / RAND_MAX;
}

/**
 * Класс оружия
 */
class Weapon {
    int magazineSize;  // Размер магазина
    int bulletsLeft;   // Остаток патронов
    bool singleShot;   // Режим одиночной стрельбы
    double fireRate;   // Скорострельность
public:
    /**
     * Конструктор оружия
     * @param magazineSize Размер магазина
     * @param fireRate Скорострельность (секунды на один выстрел)
     */
    Weapon(int magazineSize, double fireRate)
        : magazineSize(magazineSize), bulletsLeft(magazineSize), fireRate(fireRate), singleShot(true) {}

    /**
     * Перезаряжает оружие до полного магазина
     */
    void reload() {
        bulletsLeft = magazineSize;
    }

    /**
     * Переключает режим стрельбы (одиночный/очередь)
     */
    void switchFireMode() {
        singleShot = !singleShot;
    }

    /**
     * Стреляет по мишени
     * @param target Мишень, по которой ведётся огонь
     * @param targetNumber Номер мишени
     * @return Возвращает true, если попадание состоялось, иначе false
     */
    bool shoot(Target& target, int targetNumber) {
        if (bulletsLeft <= 0) {
            std::cout << "No bullets left, reloading...\n";
            reload();
            return false;
        }

        int shotsFired = singleShot ? 1 : std::min(3, bulletsLeft);  // Считаем, сколько патронов реально можем использовать
        double chance = target.calculateHitChance();
        double shotResult = getRandomDouble();

        if (shotResult <= chance) {
            target.takeDamage(shotsFired);
            std::cout << (singleShot ? "Single shot" : "Burst shot") << " hit the target #" << targetNumber + 1 << "!\n";
            std::cout << "Current hits on target #" << targetNumber + 1 << ": " << target.getCurrentHits() << "\n";
            bulletsLeft -= shotsFired;
            return true;
        }
        else {
            std::cout << (singleShot ? "Single shot" : "Burst shot") << " missed target #" << targetNumber + 1 << "!\n";
            bulletsLeft -= shotsFired;
            return false;
        }
    }


    /**
     * Получает скорострельность оружия
     * @return Скорострельность в секундах на выстрел
     */
    double getFireRate() const {
        return fireRate;
    }

    /**
     * Перегрузка оператора вывода информации об оружии
     * @param os Ссылка на поток вывода
     * @param weapon Ссылка на объект оружия
     * @return Ссылка на поток вывода с информацией об оружии
     */
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Weapon { Magazine Size: " << weapon.magazineSize << ", Bullets Left: "
            << weapon.bulletsLeft << ", Fire Rate: " << weapon.fireRate
            << ", Mode: " << (weapon.singleShot ? "Single" : "Burst") << " }";
        return os;
    }
};

/**
 * Класс стрельбища
 */
class ShootingRange {
    Weapon weapon;
    Target* targets[10];
    int numTargets;
    double simulationTime;
public:
    /**
     * Конструктор стрельбища
     * @param weapon Оружие, используемое на стрельбище
     * @param simulationTime Время симуляции в секундах
     */
    ShootingRange(Weapon weapon, double simulationTime)
        : weapon(weapon), simulationTime(simulationTime), numTargets(0) {}

    /**
     * Добавляет мишень на стрельбище
     * @param target Указатель на мишень
     */
    void addTarget(Target* target) {
        if (numTargets < 10) {
            targets[numTargets++] = target;
        }
        else {
            std::cout << "Maximum number of targets reached!\n";
        }
    }

    /**
     * Запускает симуляцию стрельбы по мишеням
     */
    void simulate() {
        double timeLeft = simulationTime;
        int destroyedTargets = 0;
        int totalHits = 0;

        while (timeLeft > 0) {
            for (int i = 0; i < numTargets; ++i) {
                if (!targets[i]->isDestroyed()) {
                    bool hit = weapon.shoot(*targets[i], i);
                    if (hit) {
                        totalHits++;
                        if (targets[i]->isDestroyed()) {
                            destroyedTargets++;
                            std::cout << "Target #" << i + 1 << " is destroyed!\n";
                        }
                    }
                }
            }
            if (getRandomDouble() > 0.8) {
                weapon.switchFireMode();
            }
            timeLeft -= weapon.getFireRate();
        }

        std::cout << "Simulation over!\n";
        std::cout << "Destroyed targets: " << destroyedTargets << "\n";
        std::cout << "Remaining targets: " << numTargets - destroyedTargets << "\n";
        std::cout << "Total hits: " << totalHits << "\n";

        std::cout << "\nFinal target statistics:\n";
        for (int i = 0; i < numTargets; ++i) {
            std::cout << "Target #" << i + 1 << " - Visibility: " << targets[i]->getVisibility()
                << ", Max Hits: " << targets[i]->getMaxHits()
                << ", Current Hits: " << targets[i]->getCurrentHits()
                << ", Status: " << (targets[i]->isDestroyed() ? "Destroyed" : "Active") << "\n";
        }
    }

    /**
     * Перегрузка оператора вывода информации о стрельбище
     * @param os Ссылка на поток вывода
     * @param range Ссылка на объект стрельбища
     * @return Ссылка на поток вывода с информацией о стрельбище
     */
    friend std::ostream& operator<<(std::ostream& os, const ShootingRange& range) {
        os << "ShootingRange { " << range.weapon << ", Number of Targets: " << range.numTargets << " }";
        return os;
    }
};

/**
 * Главная программа
 */
int main() {
    srand(time(0));

    Weapon myWeapon(30, 5);

    ShootingRange range(myWeapon, 60);

    int numTargets = rand() % 5 + 3;
    for (int i = 0; i < numTargets; ++i) {
        double distance = rand() % 100 + 50;
        int maxHits = rand() % 5 + 1;
        bool reflective = rand() % 2;

        if (rand() % 2 == 0) {
            double radius = rand() % 20 + 10;
            range.addTarget(new CircularTarget(radius, distance, reflective, maxHits));
        }
        else {
            double side = rand() % 20 + 10;
            range.addTarget(new SquareTarget(side, distance, reflective, maxHits));
        }
    }

    range.simulate();
    std::cout << range << "\n";

    return 0;
}
