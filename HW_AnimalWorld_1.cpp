#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Базовый класс континента
class Continent {
protected:
    string name;

public:
    Continent() {}

    virtual ~Continent() {}

    void SetName(const string& name) {
        this->name = name;
    }

    virtual void Populate() = 0;

    const string& GetName() const {
        return name;
    }
};

// Класс для континента Африка, наследуется от Continent
class Africa : public Continent {
public:
    Africa() {
        SetName("Africa");
    }

    void Populate() {
        cout << "Populating Africa with animals...\n";
    }
};

// Класс для континента Северная Америка, наследуется от Continent
class NorthAmerica : public Continent {
public:
    NorthAmerica() {
        SetName("North America");
    }

    void Populate() {
        cout << "Populating North America with animals...\n";
    }
};

// Базовый класс для животных
class Animal {
protected:
    string description;

public:
    Animal() {}

    virtual ~Animal() {}

    void SetDescription(const string& description) {
        this->description = description;
    }

    virtual void Eat() {}
};

// Класс для травоядных животных, наследуется от Animal
class Herbivore : public Animal {
protected:
    double weight;
    bool isAlive;

public:
    Herbivore(double weight = 0, bool status = true) {
        SetWeight(weight);
        SetLife(status);
    }

    virtual ~Herbivore() {}

    void SetWeight(double weight) {
        this->weight = weight;
    }
    // Установка состояния (живо или нет)
    void SetLife(bool status) {
        isAlive = status;
    }

    void EatGrass() {
        weight += 10;
    }

    double GetWeight() const {
        return weight;
    }
    // Проверка, живо ли животное
    bool IsAlive() const {
        return isAlive;
    }
};

class Wildebeest : public Herbivore {
public:
    Wildebeest() {
        SetDescription("Wildebeest");
        SetWeight(100);
    }
    virtual ~Wildebeest() {
        cout << "Wildebeest destroyed\n";
    }
    void EatGrass() {
        Herbivore::EatGrass();
    }
};

class Bison : public Herbivore {
public:
    Bison() {
        SetDescription("Bison");
        SetWeight(200);
    }
    virtual ~Bison() {
        cout << "Bison destroyed\n";
    }
    void EatGrass() {
        Herbivore::EatGrass();
    }
};

// Класс для плотоядных животных, наследуется от Animal
class Carnivore : public Animal {
protected:
    int power;

public:
    Carnivore() {
        SetPower(50);
    }

    virtual ~Carnivore() {
        cout << "Carnivore destroyed: " << description << "\n";
    }

    void SetPower(int power) {
        this->power = power;
    }

    int GetPower() const {
        return power;
    }

    void Eat(Herbivore* herbivore) {
        // Проверяем, что указатель на травоядного не нулевой и травоядное живо
        if (herbivore && herbivore->IsAlive()) {
            // Проверяем, сила хищника больше или равна весу травоядного
            if (power >= herbivore->GetWeight()) {
                // Если сила хищника достаточна, он съедает травоядного
                // Увеличиваем силу хищника на 10
                power += 10;
                // Устанавливаем травоядному статус мертвого
                herbivore->SetLife(false);
            }
            else {
                // Если сила хищника меньше веса травоядного, хищник теряет силу
                power -= 10;
                // Проверяем, чтобы сила хищника не стала отрицательной
                if (power < 0) {
                    // Если сила отрицательная, устанавливаем её в 0
                    power = 0; // Хищник не может иметь отрицательную силу
                }
            }
        }
    }
};

// Разновидности плотоядных
class Lion : public Carnivore {
public:
    Lion(int power = 50) {
        SetDescription("Lion");
        SetPower(power);
    }

    ~Lion() {
        cout << "Lion destroyed\n";
    }

    void Eat(Herbivore* herbivore) {
        Carnivore::Eat(herbivore);
    }
};

class Wolf : public Carnivore {
public:
    Wolf(int power = 50) {
        SetDescription("Wolf");
        SetPower(power);
    }

    ~Wolf() {
        cout << "Wolf destroyed\n";
    }

    void Eat(Herbivore* herbivore) {
        Carnivore::Eat(herbivore);
    }
};


// Класс, представляющий мир животных
class AnimalWorld {
private:
    vector<Continent*> continents;
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
    ~AnimalWorld() {
        for (auto continent : continents) {
            delete continent;
        }
        for (auto herbivore : herbivores) {
            delete herbivore;
        }
        for (auto carnivore : carnivores) {
            delete carnivore;
        }
    }

    // Добавление континента
    void AddContinent(Continent* continent) {
        continents.push_back(continent);
    }

    // Население мира животных
    void PopulateWorld() {
        for (auto continent : continents) {
            continent->Populate();
        }
    }

    // Кормление травоядных
    void MealsHerbivores() {
        cout << "Herbivores eat grass...\n";
        for (auto herbivore : herbivores) {
            herbivore->Eat();
        }
    }

    // Питание хищников
    void NutritionCarnivores() {
        cout << "Carnivores hunting on herbivores...\n";
        for (auto carnivore : carnivores) {
            for (auto herbivore : herbivores) {
                carnivore->Eat(herbivore);
            }
        }
    }

    // Добавляет травоядное животное в мир животных
    void AddHerbivore(Herbivore* herbivore) {
        herbivores.push_back(herbivore);
    }

    // Добавляет плотоядное животное в мир животных
    void AddCarnivore(Carnivore* carnivore) {
        carnivores.push_back(carnivore);
    }
};

int main() {

    // Создание объекта мира животных
    AnimalWorld world;

    // Создание и добавление объекта континентов в мир животных
    Continent* africa = new Africa;
    world.AddContinent(africa);

    Continent* northAmerica = new NorthAmerica;
    world.AddContinent(northAmerica);

    // Население мира животных (заполнение континентов животными)
    world.PopulateWorld();

    // Создание и добавление объекта травоядного и плотоядного в мир животных
    Wildebeest* wildebeest = new Wildebeest;
    world.AddHerbivore(wildebeest);

    Lion* lion = new Lion;
    world.AddCarnivore(lion);

    //Питание животных
    world.MealsHerbivores();
    world.NutritionCarnivores();

}

