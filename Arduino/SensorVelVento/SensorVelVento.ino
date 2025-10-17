#define SENSOR_PIN 35    // Pino digital conectado ao sensor
#define HOLES 10         // Número de furos no disco
#define DIAMETER 0.03    // Diâmetro do disco (m)

volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;

// Fator de calibração (ajuste após testar com anemômetro real)
float k = 1.0;  // comece com 1.0, ajuste depois

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulse, FALLING);

  Serial.println("=== Medidor de velocidade do vento ===");
  Serial.println("Tempo(s)\tVelocidade(m/s)");
}

void loop() {
  unsigned long currentTime = millis();

  // Calcula a cada 1 segundo
  if (currentTime - lastTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));

    unsigned long pulses = pulseCount;
    pulseCount = 0;
    lastTime = currentTime;

    // Calcula rotações por segundo (RPS)
    float rps = (float)pulses / HOLES;

    // Circunferência do disco (C = π * D)
    float circumference = 3.1416 * DIAMETER;

    // Velocidade linear da borda (m/s)
    float windSpeed = k * rps * circumference;   // m/s
    float windSpeed_kmh = windSpeed * 3.6;       // km/h
    
    Serial.print("Segundo: ");
    Serial.print((float)currentTime / 1000.0);
    Serial.print("\t");
    
    Serial.print("Velocidade: ");
    Serial.print(windSpeed, 3);
    Serial.print(" m/s (");
    Serial.print(windSpeed_kmh, 2);
    Serial.println(" km/h)");


    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulse, FALLING);
  }
}
