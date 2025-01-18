int soundPin = A0;            // KY-038 подключен к A0
int ledPins[6] = {3, 4, 5, 6, 7, 8}; // Пины для светодиодов

int thresholds[6][2] = { {0, 50}, {50, 100}, {100, 200}, {200, 300}, {300, 400}, {400, 1024} };

int lastAverage = 0;          // Предыдущее усреднённое значение
int noChangeCounter = 0;      // Счётчик отсутствия изменений
const int maxNoChange = 10;   // Порог для выключения лампочек

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT); // Настраиваем пины светодиодов как выходы
  }
  Serial.begin(9600); // Инициализация последовательного монитора
}

void loop() {
  int soundLevel = analogRead(soundPin); // Считываем уровень звука
  int adjustedSound = abs(soundLevel - 500); // Центрируем относительно 500
  
  Serial.println(adjustedSound); // Выводим скорректированный уровень звука

  // Проверяем, изменяется ли усреднённое значение
  if (abs(adjustedSound - lastAverage) < 5) { // Изменение меньше 5 единиц
    noChangeCounter++;
  } else {
    noChangeCounter = 0; // Сброс счётчика при изменении
  }

  // Если звук не изменяется длительное время, выключаем все лампочки
  if (noChangeCounter >= maxNoChange) {
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    return; // Выходим из loop, чтобы не обрабатывать дальше
  }

  // Сохраняем текущее значение как предыдущее
  lastAverage = adjustedSound;

  // Выключаем все светодиоды
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Включаем светодиоды в зависимости от уровня звука
  for (int i = 0; i < 6; i++) {
    if (adjustedSound >= thresholds[i][0] && adjustedSound < thresholds[i][1]) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  delay(50); // Небольшая задержка для стабильности
}
