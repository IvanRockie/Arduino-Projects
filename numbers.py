const int ledPins[] = {6, 5, 2, 3, 4, 8, 7}; // Сегменты A, B, C, D, E, F, G

// Таблица сегментов для цифр 0-9
const int digitToSegments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

// Проверка числа на простоту
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Отображение цифры на дисплее
void displayDigit(int digit) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(ledPins[i], digitToSegments[digit][i]);
    }
}

// Очистка дисплея
void clearDisplay() {
    for (int i = 0; i < 7; i++) {
        digitalWrite(ledPins[i], LOW);
    }
}

// Отображение числа
void displayNumber(int number) {
    int ones = number % 10;         // Единицы
    int tens = (number / 10) % 10;  // Десятки
    int hundreds = (number / 100) % 10; // Сотни
    int thousands = (number / 1000) % 10; // Тысячи

    // Отображаем тысячи, если число >= 1000
    if (thousands > 0) {
        displayDigit(thousands);
        delay(250); // Пауза
        clearDisplay();
        delay(250); // Пауза перед следующей цифрой
    }

    // Отображаем сотни, если число >= 100
    if (hundreds > 0 || thousands > 0) {
        displayDigit(hundreds);
        delay(250); // Пауза
        clearDisplay();
        delay(250); // Пауза перед следующей цифрой
    }

    // Отображаем десятки, если число >= 10
    if (tens > 0 || hundreds > 0 || thousands > 0) {
        displayDigit(tens);
        delay(250); // Пауза
        clearDisplay();
        delay(250); // Пауза перед следующей цифрой
    }

    // Отображаем единицы
    displayDigit(ones);
    delay(300); // Пауза
    clearDisplay();
    delay(200); // Пауза перед следующим числом
}

void setup() {
    for (int i = 0; i < 7; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop() {
    int primeCount = 0; // Счётчик простых чисел

    for (int number = 2; ; number++) {
        if (isPrime(number)) {
            primeCount++; // Увеличиваем счётчик простых чисел

            // Отображаем текущее простое число
            displayNumber(number);
            
            // Отображаем порядковый номер
            delay(500);
            displayNumber(primeCount);
            delay(3000);
        }
    }
}
