// Network checker on esp-01s
//
//   https://blynk.cloud/dashboard/templates

#define BLYNK_FIRMWARE_VERSION "2023.0626.20"

#define BLYNK_TEMPLATE_ID "****"
#define BLYNK_TEMPLATE_NAME "Network Checker"
#define BLYNK_AUTH_TOKEN "****"

// Your WiFi credentials.
// Set password to "" for open networks.
#define WIFI_SSID "****"
#define WIFI_PASS "****"

#define BLYNK_PRINT Serial  // Comment this out to disable serial monitor prints

// Adding the required libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <ESPping.h>
#include <ESP8266mDNS.h>

BlynkTimer timer; 

const IPAddress ip_or_host(114, 114, 114, 114);
unsigned long next_ping = 2000;

// esp-01s 引脚
#define PIN_Button 0
#define PIN_LED_Red 1
#define PIN_LED_Blue 2
#define PIN_Relay 3 

// 备用
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if (value == 1)
  {
    digitalWrite(PIN_LED_Red, HIGH);
  }
  else
  {
    digitalWrite(PIN_LED_Red, LOW);
  }
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  if (value == 1)
  {
    digitalWrite(PIN_LED_Blue, HIGH);
  }
  else
  {
    digitalWrite(PIN_LED_Blue, LOW);
  }
}

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  if (value == 1)
  {
    digitalWrite(PIN_Relay, HIGH);
  }
  else
  {
    digitalWrite(PIN_Relay, LOW);
  }
}

//
void setup()
{
  // Debug console
  Serial.begin(115200);                         // Make sure you have the same baud rate in your serial monitor set up
  pinMode(PIN_LED_Red, OUTPUT);              
  digitalWrite(PIN_LED_Red, HIGH);
  pinMode(PIN_LED_Blue, OUTPUT);              
  digitalWrite(PIN_LED_Blue, HIGH);
  pinMode(PIN_Relay, OUTPUT);  
  digitalWrite(PIN_Relay, HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  timer.setInterval(1000L, myTimer); 
  Blynk.syncAll();
}


void myTimer()
{
  if(millis() > next_ping){
    if(Ping.ping(ip_or_host)){
      int ping_ms = Ping.averageTime();
      Blynk.virtualWrite(V3, WiFi.RSSI());
      Blynk.virtualWrite(V4, WiFi.localIP().toString().c_str());
      Blynk.virtualWrite(V5, ping_ms);
      next_ping = millis() + 2000;
    } else {
        digitalWrite(PIN_Relay, HIGH);
        delay(500);
        digitalWrite(PIN_Relay, LOW);
        delay(1500);
        digitalWrite(PIN_Relay, HIGH);
        delay(120000);
    }
  }
}


void loop()
{
  Blynk.run(); // Blynk magic happens here
  timer.run(); // runs BlynkTimer
}
