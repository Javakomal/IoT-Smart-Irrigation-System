IoT-Based Smart Irrigation System: Optimizing Water Usage in Agriculture

Team Members
- Khushi Solanki (60005230055)  
- Komal Kushwaha (60005230116)  
- Nihal Singh (60005230221)  

Problem Statement
Agriculture consumes nearly 70% of global freshwater, yet inefficient irrigation leads to up to 50% water wastage. Under-irrigation reduces crop yield by 20–40%. Farmers spend significant time monitoring fields without accurate data, and unreliable weather predictions worsen the situation. These factors result in economic losses and unsustainable farming practices.

Proposed Solution
This project develops an IoT-based smart irrigation system that:
- Continuously monitors soil moisture levels  
- Uses temperature and humidity data for better decisions  
- Automatically controls water supply  
- Stops irrigation once optimal moisture is reached  

This reduces water wastage, saves energy, and minimizes manual effort.

Tech Stack / Components Used
- ESP32 / Arduino UNO  
- Soil Moisture Sensor  
- DHT11/DHT22 Sensor  
- Relay Module  
- Water Pump  
- Arduino IDE  
- Wokwi Simulation Platform
    
Code
/*
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
