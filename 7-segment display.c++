const int ledPins[] = {7, 8, 2, 3, 4, 5, 6}; // Сегменты A, B, C, D, E, F, G

// Таблица сегментов для каждой цифры
// A, B, C, D, E, F, G
const bool digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0 -> A, B, C, D, E, F
  {0, 1, 1, 0, 0, 0, 0}, // 1 -> B, C
  {1, 1, 0, 1, 1, 0, 1}, // 2 -> A, B, D, E, G
  {1, 1, 1, 1, 0, 0, 1}, // 3 -> A, B, C, D, G
  {0, 1, 1, 0, 0, 1, 1}, // 4 -> B, C, F, G
  {1, 0, 1, 1, 0, 1, 1}, // 5 -> A, C, D, F, G
  {1, 0, 1, 1, 1, 1, 1}, // 6 -> A, C, D, E, F, G
  {1, 1, 1, 0, 0, 0, 0}, // 7 -> A, B, C
  {1, 1, 1, 1, 1, 1, 1}, // 8 -> A, B, C, D, E, F, G
  {1, 1, 1, 1, 0, 1, 1}  // 9 -> A, B, C, D, F, G
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

void loop() {
  int delayTime = 1000; // Задержка между цифрами

  // Поочередное отображение цифр от 0 до 9
  for (int digit = 0; digit <= 9; digit++) {
    displayDigit(digit); // Отображаем текущую цифру
    delay(delayTime);    // Задержка
  }
}
