#include <WiFi.h>
#define RED 3
#define GREEN 4
#define BLUE 5

const char* ssid     = "SUPERONLINE_Wi-Fi_3C40";
const char* password = "BWZkVACS3Q";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(RED,OUTPUT);
    pinMode(GREEN,OUTPUT);
    pinMode(BLUE,OUTPUT);
    delay(100);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();

}

void loop(){
 WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");           
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
       
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("RED COLOR  <a href=\"/RON\"> CLICK </a> LED ON.<br>");
            client.print("RED COLOR <a href=\"/ROFF\"> CLICK </a> LED OFF.<br>");
            
            client.print("GREEN COLOR <a href=\"/GON\"> CLICK </a> LED ON.<br>");
            client.print("GREEN COLOR <a href=\"/GOFF\"> CLICK </a> LED OFF.<br>");
            
            client.print("BLUE COLOR <a href=\"/BON\"> CLICK </a> LED ON.<br>");
            client.print("BLUE COLOR <a href=\"/BOFF\"> CLICK </a> LED OFF.<br>");
            
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /RON")) {
          digitalWrite(RED, HIGH);
        }
        if (currentLine.endsWith("GET /GON")) {
          digitalWrite(GREEN, HIGH);
        }
        if (currentLine.endsWith("GET /BON")) {
          digitalWrite(BLUE, HIGH);
        }        



        if (currentLine.endsWith("GET /ROFF")) {
          digitalWrite(RED, LOW);
        }
        if (currentLine.endsWith("GET /GOFF")) {
          digitalWrite(GREEN, LOW);
        }
        if (currentLine.endsWith("GET /BOFF")) {
          digitalWrite(BLUE, LOW);
        }
    
      }
    }








    //client.stop();
    //Serial.println("Client Disconnected.");
  }
}
