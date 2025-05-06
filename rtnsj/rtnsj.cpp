#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Класс для хранения и проверки списка городов
class CityList {
private:
    vector<string> usedCities;

public:
    void addCity(const string& city) {
        usedCities.push_back(city);
    }

    bool isCityUsed(const string& city) {
        string lowerCity = city;
        transform(lowerCity.begin(), lowerCity.end(), lowerCity.begin(), ::tolower);
        return find(usedCities.begin(), usedCities.end(), lowerCity) != usedCities.end();
    }

    bool isEmpty() const {
        return usedCities.empty();
    }
};

// Класс для управления ходом игрока
class PlayerTurn {
private:
    char expectedLetter;

public:
    PlayerTurn() : expectedLetter('\0') {} // Изначально нет ожидаемой буквы

    char getExpectedLetter() const {
        return expectedLetter;
    }

    void setExpectedLetter(char letter) {
        expectedLetter = tolower(letter);
    }

    bool checkFirstLetter(const string& city) const {
        if (expectedLetter == '\0') return true; // Первый ход — любая буква
        return tolower(city[0]) == expectedLetter;
    }
};

// Класс для управления игрой
class CityGame {
private:
    CityList cityList;
    PlayerTurn playerTurn;

public:
    void startGame() {
        string city;

        cout << "Добро пожаловать в игру 'Города'!\n";
        cout << "Введите город (для выхода введите 'exit'):\n";

        while (true) {
            cin >> city;

            if (city == "exit") break;

            // Приводим к нижнему регистру для проверки
            string lowerCity = city;
            transform(lowerCity.begin(), lowerCity.end(), lowerCity.begin(), ::tolower);

            // Проверка, был ли город уже назван
            if (cityList.isCityUsed(lowerCity)) {
                cout << "Этот город уже был! Игра завершена.\n";
                break;
            }

            // Проверка первой буквы
            if (!playerTurn.checkFirstLetter(lowerCity)) {
                cout << "Город должен начинаться на '" << (char)toupper(playerTurn.getExpectedLetter()) << "'! Игра завершена.\n";
                break;
            }

            cityList.addCity(lowerCity);
            cout << "Город добавлен. Последняя буква: " << lowerCity.back() << endl;

            // Устанавливаем ожидаемую букву для следующего хода
            playerTurn.setExpectedLetter(lowerCity.back());
            cout << "Следующий игрок, назови город на букву '" << (char)toupper(playerTurn.getExpectedLetter()) << "': ";
        }

        cout << "Игра завершена!\n";
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    CityGame game;
    game.startGame();
    return 0;
}