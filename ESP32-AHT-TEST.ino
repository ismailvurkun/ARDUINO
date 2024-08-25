#include <Adafruit_AHTX0.h>
#define LED1 3
#define LED2 4
#define LED3 5

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    digitalWrite(LED1,HIGH);
    while (1) delay(1000);
  }
  digitalWrite(LED1,LOW);

  Serial.println("AHT10 or AHT20 found");
  digitalWrite(LED2,HIGH);
}

void loop() {
  digitalWrite(LED2,LOW);
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  digitalWrite(LED3,HIGH);
  delay(2000);
  digitalWrite(LED3,LOW);
  delay(500);
}