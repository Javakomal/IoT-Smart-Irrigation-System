/*
  Smart Irrigation System using ESP32

  Components:
  - Soil Moisture Sensor (Analog)
  - Relay Module (Pump Control)
  - DHT11 Sensor (Temperature & Humidity)

  Function:
  - Reads soil moisture
  - Automatically turns pump ON/OFF
  - Displays data on Serial Monitor
*/

#include <DHT.h>

// ---------------- PIN DEFINITIONS ----------------
#define SOIL_SENSOR_PIN 34     // Analog pin
#define RELAY_PIN 26           // Relay control pin
#define DHT_PIN 4              // DHT data pin
#define DHT_TYPE DHT11

// ---------------- OBJECTS ----------------
DHT dht(DHT_PIN, DHT_TYPE);

// ---------------- VARIABLES ----------------
int soilValue = 0;
int soilThreshold = 2000;   // Adjust based on testing

float temperature = 0;
float humidity = 0;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF initially (depends on module logic)
  digitalWrite(RELAY_PIN, HIGH);

  dht.begin();

  Serial.println("=================================");
  Serial.println(" Smart Irrigation System Started ");
  Serial.println("=================================");
}

// ---------------- MAIN LOOP ----------------
void loop() {

  // Read soil moisture
  soilValue = analogRead(SOIL_SENSOR_PIN);

  // Read DHT values
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Print data
  Serial.println("\n----- Sensor Data -----");

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Decision making
  if (soilValue > soilThreshold) {
    Serial.println("Status: Soil Dry → Pump ON");
    digitalWrite(RELAY_PIN, LOW);   // Relay ON
  } 
  else {
    Serial.println("Status: Soil Wet → Pump OFF");
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
  }

  delay(3000);
}
