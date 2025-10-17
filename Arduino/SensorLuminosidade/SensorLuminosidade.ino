#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL — pinos padrão do ESP32
  Serial.println("Iniciando sensor BH1750...");

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Sensor BH1750 iniciado com sucesso!");
  } else {
    Serial.println("Falha ao inicializar o sensor BH1750. Verifique conexões.");
    while (1);
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();

  if (lux < 0) {
    Serial.println("Erro na leitura do sensor!");
  } else {
    Serial.print("Luminosidade: ");
    Serial.print(lux);
    Serial.println(" lux");
  }

  delay(1000);
}
