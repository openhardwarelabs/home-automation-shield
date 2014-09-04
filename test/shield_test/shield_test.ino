/*************************************************** 
  This is a sketch to test the HA Shield
  
  Written by Marco Schwartz for Open Home Automation
 ****************************************************/
 
 // Libraries
 #include "DHT.h"
 
 // DHT sensor
#define DHTPIN 8 
#define DHTTYPE DHT11
 
const int relay_pin = 7; // Relay pin
const int sensor_pin = A1; // Sensor pin
const int photocell_pin = A0; // Photocell pin
const int contact_pin = 6; // Contact sensor pin
const int motion_pin = 2; // Motion sensor pin

// DHT instance
DHT dht(DHTPIN, DHTTYPE);

// Define measurement variables
float amplitude_current;
float effective_value;
float effective_voltage = 230; // Set voltage to 230V (Europe) or 110V (US)
float effective_power;
float zero_sensor;

void setup() {
  Serial.begin(115200);
  
  // Setup relay output
  pinMode(relay_pin,OUTPUT);
  digitalWrite(relay_pin, LOW);
  
  // Init DHT
  dht.begin();
  
  // Calibrate sensor with null current
  zero_sensor = getSensorValue();
  Serial.print("Zero point sensor: ");
  Serial.println(zero_sensor);
  Serial.println("");
  
  delay(2000);
}

void loop() {
  
  // Activate relay
  digitalWrite(relay_pin, HIGH);
  
   // Perform power measurement
  float sensor_value = getSensorValue();
  Serial.print("Sensor value relay ON: ");
  Serial.println(sensor_value);
  
  // Wait for 1 second
  delay(2000);
  
   // Deactivate relay
  digitalWrite(relay_pin, LOW);
  
  // Perform power measurement
  sensor_value = getSensorValue();
  Serial.print("Sensor value relay OFF: ");
  Serial.println(sensor_value);
  
  // Wait for 1 second
  delay(2000);
  
  // Read light level
  float sensor_reading = analogRead(photocell_pin);
  float light = sensor_reading/1024*100;
  
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println("%");
  Serial.println("");
  
  // Measure from DHT
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Display temperature
  Serial.print("Temperature: ");
  Serial.print((int)temperature);
  Serial.println(" C");
  
   // Display humidity
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  // Test contact sensor
  Serial.println("Testing contact sensor ...");
  delay(2000);
  
  int contact_reading = digitalRead(contact_pin);
  Serial.print("Contact sensor reading: ");
  Serial.println(contact_reading);
  
  // Test motion sensor
  Serial.println("Testing motion sensor ...");
  delay(2000);
  
  int motion_reading = digitalRead(motion_pin);
  Serial.print("Motion sensor reading: ");
  Serial.println(motion_reading);
 
}

// Get the reading from the current sensor
float getSensorValue()
{
  int sensorValue;
  float avgSensor = 0;
  int nb_measurements = 100;
  for (int i = 0; i < nb_measurements; i++) {
    sensorValue = analogRead(sensor_pin);
    avgSensor = avgSensor + float(sensorValue);
  }	  
  avgSensor = avgSensor/float(nb_measurements);
  return avgSensor;
}
