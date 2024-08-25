#define LED1 3
#define LED2 4
#define LED3 5

void setup() {
  
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);

}

void loop() {
 digitalWrite(LED2,HIGH);
 //delay(1000);
 //digitalWrite(LED2,HIGH);
 //delay(1000);
 digitalWrite(LED1,HIGH);
 //delay(500);
 //digitalWrite(LED3,LOW);
 //delay(1000);
 //digitalWrite(LED2,LOW);
 //delay(1000);
 //digitalWrite(LED2,LOW);
 //delay(500);
}
