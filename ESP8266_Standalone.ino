/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

     Downloads, docs, tutorials: http://www.blynk.cc
     Blynk community:            http://community.blynk.cc
     Social networks:            http://www.fb.com/blynkapp
                                 http://twitter.com/blynk_app

   Blynk library is licensed under MIT license
   This example code is in public domain.

 **************************************************************
   This example runs directly on ESP8266 chip.

   You need to install this for ESP8266 development:
     https://github.com/esp8266/Arduino

   Please be sure to select the right ESP8266 module
   in the Tools -> Board menu!

   Change WiFi ssid, pass, and Blynk auth token to run :)

 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>
#include <SimpleTimer.h>

char auth[] = "NuWBLX1Oz3sTrMgyfRIsw7sZ2HPH1-Pp";

#define tempSenzorPin 2
dht DHT;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "No Free Internet For You ! :)";
char pass[] = "CiscoVidiu2020";

SimpleTimer timer;

void sendSensor()
{
  DHT.read11(tempSenzorPin);
  float t = DHT.temperature;

  if (isnan(t)) {
    Serial.println("Nu se poate citi temperatura de la senzor.");
    return;
  }
  else
    Serial.println(t);

  Blynk.virtualWrite(V6, t);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  DHT.read11(tempSenzorPin);
  pinMode(D7, INPUT);
  
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
