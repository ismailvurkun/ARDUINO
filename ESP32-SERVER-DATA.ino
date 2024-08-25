#include <WiFi.h>
#define RED 3
#define GREEN 4
#define BLUE 5
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

const char* ssid     = "SUPERONLINE_Wi-Fi_3C40";
const char* password = "BWZkVACS3Q";

WiFiServer server(80);

uint8_t DHTPin = D4;
uint8_t LED1pin = D2;
bool LED1status = LOW; //durumlarını tanımlıyoruz.
uint8_t LED2pin = D3;
bool LED2status = LOW;
               
// DHT'yi tanımlıyoruz..
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
    Serial.begin(115200);
    pinMode(RED,OUTPUT);
    pinMode(GREEN,OUTPUT);
    pinMode(BLUE,OUTPUT);
    delay(100);

  dht.begin();              

  Serial.println("wifi'ya bağlanılıyor ");
  Serial.println(ssid);

  //yerel ağınıza bağlanmanız için gerekli komut
  WiFi.begin(ssid, password);

  //bağlantı gerçekleştiğini kontrol ediyoruz
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print("."); //bağlantı sağlanana kadar ekranda "." çıkmasını sağlıyoruz.(Loading gibi)
  }
  Serial.println("");
  Serial.println("WiFi Bağlandı..!");
  Serial.print("IP Adresiniz: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect); //Bağlantı sağlandıktan sonra server kontrolleri.
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Sunucusu Başladı");

}
void loop() {
  
  server.handleClient(); 
   if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}
  
}

void handle_OnConnect() {

  Temperature = dht.readTemperature(); // 
  Humidity = dht.readHumidity(); // 
  LED1status = LOW;
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,LED2status)); 
}
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("D2 Durumu: ON");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,true,LED2status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("D2 Durumu: OFF");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,false,LED2status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("D3 Durumu: ON");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("D3 Durumu: OFF");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat,uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 NodeMCU Akilli Ev</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c ;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #0095c7;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body bgcolor= BlanchedAlmond style=color:white>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU Akilli Ev</h1>\n";
  
  ptr +="<p>SICAKLIK: ";
  ptr +=(int)Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p>NEM: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  if(led1stat)
  {ptr +="<p>LED1 Durum: ACIK</p><a class=\"button button-off\" href=\"/led1off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED1 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led1on\">AC</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Durum: ACIK</p><a class=\"button button-off\" href=\"/led2off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED2 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led2on\">AC</a>\n";}


  //Robolink Logo
  ptr += "<a target=”_blank” a href='https://www.robolinkmarket.com'>";
  ptr += "<br/><br/><img src= 'https://akademi.robolinkmarket.com/wp-content/uploads/2018/10/RLT1_Logo-309×90-Copy.png' Z\" width=\"240\" height=\"70\" alt=\"logo\\\">\n";
  ptr += "<br/><br/><iframe width='560' height='315' src='https://www.youtube.com/embed/xSpENoUZJkU' title='YouTube video player' frameborder='0' allow='accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture' allowfullscreen></iframe>" ;
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}