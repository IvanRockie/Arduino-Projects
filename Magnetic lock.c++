#include <Keypad.h>

// Настройка клавиатуры 4x4
const byte ROWS = 4; // Число строк
const byte COLS = 4; // Число столбцов

// Символы на клавишах
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Пины для строк и столбцов клавиатуры
byte rowPins[ROWS] = {3, 10, 4, 5}; // R1, R2, R3, R4
byte colPins[COLS] = {2, 7, 9, 6};  // C1, C2, C3, C4

// Инициализация клавиатуры
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Пин для управления реле
const int relayPin = 12;

// Переменная для хранения пароля
String password = "1234"; // Установленный пароль
String inputPassword = ""; // Введенный пароль

void setup() {
  pinMode(relayPin, OUTPUT); // Настраиваем пин реле как выход
  digitalWrite(relayPin, HIGH); // Реле выключено (замок закрыт)
  Serial.begin(9600); // Для отладки
}

void loop() {
  char key = keypad.getKey(); // Считываем нажатую клавишу

  if (key) {
    Serial.println(key); // Печатаем нажатую клавишу для отладки

    if (key == '#') { // Если нажали #, проверяем пароль
      if (inputPassword == password) {
        Serial.println("Пароль верный, открываем замок!");
        digitalWrite(relayPin, LOW); // Включаем реле (замок открывается)
        delay(5000); // Замок открыт 5 секунд
        digitalWrite(relayPin, HIGH); // Выключаем реле (замок закрывается)
      } else {
        Serial.println("Неверный пароль!");
      }
      inputPassword = ""; // Сбрасываем введенный пароль
    } else if (key == '*') { // Если нажали *, сбрасываем ввод
      inputPassword = "";
      Serial.println("Ввод пароля сброшен");
    } else {
      inputPassword += key; // Добавляем цифру в пароль
    }
  }
}
