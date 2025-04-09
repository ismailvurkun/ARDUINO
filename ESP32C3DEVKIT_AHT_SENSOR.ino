#include <Adafruit_AHTX0.h>
#include <Wire.h>
#define LED1 3
#define LED2 4
#define LED3 5

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Serial.println("AHT10 sensör Denemesi");
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  if (! aht.begin()) {
    Serial.println("AHT Bulunamadı, Bağlantıları Kontrol Edin.");
    digitalWrite(LED1,HIGH); //KIRMIZI LED

    while (1) delay(500);
  }
  digitalWrite(LED1,LOW);
  Serial.println("AHT10 Bağlandı.");
  digitalWrite(LED3,HIGH);

}

void loop() {

delay(4000);
sensors_event_t humidity, temp;
aht.getEvent(&humidity, &temp);

Serial.print("Sıcaklık : "); 
Serial.print(temp.temperature); 
Serial.print(" C");
Serial.print(" - ");
Serial.print("Nem : "); 
Serial.print(humidity.relative_humidity); 
Serial.println("%");

digitalWrite(LED3,LOW);
digitalWrite(LED2,HIGH);
delay(500);
digitalWrite(LED2,LOW);
digitalWrite(LED3,HIGH);
  
}