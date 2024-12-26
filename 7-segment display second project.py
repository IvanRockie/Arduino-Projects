const int ledPins[] = {7, 8, 2, 3, 4, 5, 6}; // Сегменты A, B, C, D, E, F, G

// Таблица сегментов для каждой цифры
// A, B, C, D, E, F, G
const bool digits[3][7] = {
  {1, 1, 0, 0, 0, 1, 0}, // 0 -> A, B, C, D, E, F
  {0, 0, 0, 0, 0, 0, 1}, // 1 -> B, C
  {0, 0, 1, 1, 1, 0, 0}, // 2 -> A, B, D, E, G
};

void setup() {
  // Настроим все пины как выходы
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void displayDigit(int digit) {
  // Установим состояние каждого сегмента
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], digits[digit][i] ? HIGH : LOW);
  }
}

void clearDisplay() {
  // Выключим все сегменты
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  int delayTime = 500; // Задержка между миганиями

  // Поочередное отображение цифр с миганием
  for (int digit = 0; digit < 3; digit++) {
    for (int blink = 0; blink < 3; blink++) {
      displayDigit(digit); // Включаем цифру
      delay(delayTime);    // Ждём
      clearDisplay();      // Выключаем
      delay(delayTime);    // Ждём перед следующим миганием
    }
  }
}
