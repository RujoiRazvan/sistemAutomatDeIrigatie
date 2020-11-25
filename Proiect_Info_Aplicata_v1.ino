//Proiect InfoAplicata II
//Sistem automat de udat florile (actionat prin wifi sau de la buton)
//Cabluri Rosii - 5V/3V. Cabluri Negre (Gri) - Ground.

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <dht.h>

const int buton = 5;
const int ledPin =  7;
int pompaApa = 4;
int buzzer = 6;
int senzorPamant = A0;
int valoareButon = 0;
#define tempSenzorPin 2
dht DHT;

Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8);

void setup() {
  pinMode(pompaApa, OUTPUT);
  pinMode(senzorPamant, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buton, INPUT);

  display.setRotation(2);
  Serial.begin(9600);
  display.begin();
  display.setContrast(10);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 6);
  display.println("Rujoi Razvan");

  display.setTextColor(WHITE, BLACK);

  display.println("Proiect IA II");

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println();
  display.print("Sistem automat");
  display.println("de udat plante");
  display.display();
  delay(2000);
}

void loop() {
  valoareButon = digitalRead(buton);
  int valoareSenzorPamant = analogRead(senzorPamant);
  Serial.println(valoareSenzorPamant);
  DHT.read11(tempSenzorPin);
  float temperaturaCamera = DHT.temperature;
  display.display();
  display.clearDisplay();
  display.setContrast(40);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Temperatura ");
  display.print("camera: ");
  display.print(temperaturaCamera);
  display.print("C");
  display.print("Umiditate ");
  display.print("sol: ");
  display.print(valoareSenzorPamant);
  display.print("%");
  digitalWrite(ledPin, LOW);
  noTone(buzzer);

  if (valoareSenzorPamant <= 1 || valoareButon == HIGH) {
    display.display();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 0);
    display.println("Udare in");
    display.println("     proces...");
    display.display();
    digitalWrite(ledPin, HIGH);
    digitalWrite(pompaApa, HIGH);
    tone(buzzer, 2000);
    delay(5000);
    digitalWrite(ledPin, LOW);
    digitalWrite(pompaApa, LOW);
    noTone(buzzer);
    display.clearDisplay();
    display.display();
    DHT.read11(tempSenzorPin);
    temperaturaCamera = DHT.temperature;
    display.setCursor(0, 0);
    display.println("Temperatura ");
    display.print("camera: ");
    display.print(temperaturaCamera);
    display.print("C");
  }

  delay(1000);
}
