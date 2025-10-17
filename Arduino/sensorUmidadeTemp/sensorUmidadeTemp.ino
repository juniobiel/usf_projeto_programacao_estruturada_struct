#include "DHT.h"

// === Configurações do sensor ===
#define DHTPIN 32        // Pino conectado ao DHT
#define DHTTYPE DHT11    // Altere para DHT11 se for o seu caso

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  Serial.println("Leitura do sensor DHT no ESP32");
  Serial.println("Aguardando estabilização...");
  delay(2000);
}

void loop() {
  // Aguarda 2 segundos entre as leituras (recomendado pelo fabricante)
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha na leitura do sensor DHT!");
    return;
  }

  // === Exibição no Monitor Serial (texto) ===
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %  |  Temperatura: ");
  Serial.print(t);
  Serial.println(" °C");

  // === Saída formatada para o Serial Plotter ===
  // (cada variável separada por TAB)
  Serial.print("Temperatura:");
  Serial.print(t);
  Serial.print("\tUmidade:");
  Serial.println(h);
}
