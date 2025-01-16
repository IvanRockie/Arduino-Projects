// Определяем пины
#define TRIG_PIN 2 // Пин для Trig
#define ECHO_PIN 3 // Пин для Echo
#define BUZZER_PIN 8  // Пин для зумера

// Пороговое расстояние в сантиметрах
const int distanceThreshold = 10;

void setup() {
  // Настройка пинов
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Инициализация Serial для мониторинга
  Serial.begin(9600);
}

void loop() {
  // Отправляем ультразвуковой импульс
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Читаем время возврата сигнала
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Вычисляем расстояние в сантиметрах
  int distance = duration * 0.034 / 2;

  // Выводим расстояние в Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Управляем зумером
  if (distance > 50 && distance < 100) {
    digitalWrite(BUZZER_PIN, HIGH); // Включаем зумер
    delay(100);
  } else {
     digitalWrite(BUZZER_PIN, LOW);  // Выключаем зумер
  }

  // Задержка для стабильности
  delay(10);
}
