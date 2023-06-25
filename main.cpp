
// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates

#define BLYNK_TEMPLATE_ID "****"
#define BLYNK_TEMPLATE_NAME "****"
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

const IPAddress ip_or_host(114, 114, 114, 114);

unsigned long next_ping = 2000;


#define PIN_LED 2           // LED is usually connected to D2 pin. Change if needed.
#define PIN_Relay 3 

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if (value == 0)
  {
    digitalWrite(PIN_LED, HIGH);
  }
  else
  {
    digitalWrite(PIN_LED, LOW);
  }
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  if (value == 0)
  {
    digitalWrite(PIN_Relay, HIGH);
  }
  else
  {
    digitalWrite(PIN_Relay, LOW);
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);                         // Make sure you have the same baud rate in your serial monitor set up
  pinMode(PIN_LED, OUTPUT);                    // Setting LED PIN to control it
  pinMode(PIN_Relay, OUTPUT);  

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
}

void loop()
{
  Blynk.run(); // Blynk magic happens here
if(millis() > next_ping){
    if(Ping.ping(ip_or_host)){
      int ping_ms = Ping.averageTime();
      Blynk.virtualWrite(V2, WiFi.RSSI());
      Blynk.virtualWrite(V3, WiFi.localIP().toString().c_str());
      Blynk.virtualWrite(V4, ping_ms);
      next_ping = millis() + 2000;
    }
  }
}
