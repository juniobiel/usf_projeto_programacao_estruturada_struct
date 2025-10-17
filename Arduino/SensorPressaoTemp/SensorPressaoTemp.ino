#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>  // use <Adafruit_BMP280.h> se for BMP280

Adafruit_BMP280 bmp; // Cria objeto do sensor

unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL — pinos padrão do ESP32

  Serial.println("Iniciando sensor BMP280...");

  if (!bmp.begin(0x76)) { // Endereço I2C comum (0x76 ou 0x77)
    Serial.println("❌ Sensor BMP280 não encontrado! Verifique conexões ou endereço I2C.");
    while (1);
  }

  Serial.println("✅ Sensor BMP280 detectado!");
  delay(2000);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 1000) { // leitura a cada 1s
    lastTime = currentTime;

    float temperatura = bmp.readTemperature();   // °C
    float pressao = bmp.readPressure() / 100.0F; // hPa


    // --- Saída para o Serial Monitor ---
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" °C\tPressão: ");
    Serial.print(pressao);
    Serial.print(" hPa");


    Serial.println();

    // --- Saída formatada para o Serial Plotter ---
    Serial.print("Temperatura:");
    Serial.print(temperatura);
    Serial.print("\tPressao:");
    Serial.print(pressao);

    Serial.println();
  }
}
