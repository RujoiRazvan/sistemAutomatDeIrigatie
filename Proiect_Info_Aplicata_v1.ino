//Proiect InfoAplicata II
//Sistem automat de udat plante (actionat prin wifi sau de la buton)
//Cabluri Rosii - 5V/3V. Cabluri Negre (Gri) - Ground.

#include <Adafruit_PCD8544.h>
#include <dht.h>

const int buton = 5;
const int ledPin =  7;
const int pompaApa = 4;
int buzzer = 6;
int senzorPamant = A0;
int valoareButon = 0;

#define tempSenzorPin 2
dht DHT;

Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8); //initializarea pinilor de pe lcd

void setup() {
  pinMode(pompaApa, OUTPUT);
  pinMode(senzorPamant, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buton, INPUT);
 
  Serial.begin(9600); //initializez conexiunea seriala la 9600 biti pe secunda
  
  display.begin();
  display.setRotation(2);
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
  display.println("Sistem automat");
  display.println("de udat plante");
  display.display();
  delay(2000);
}

void loop() {
  valoareButon = digitalRead(buton);
  int valoareSenzorPamant = analogRead(senzorPamant);
  
  Serial.println("Valoare senzor pamant: ");
  Serial.println(valoareSenzorPamant);
  
  DHT.read11(tempSenzorPin);
  double temperaturaCamera = DHT.temperature;
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
  display.print(valoareSenzorPamant / 100);
  display.print("%");
  digitalWrite(ledPin, LOW);
  noTone(buzzer);

  if (valoareSenzorPamant >= 900 || valoareButon == HIGH) {
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
    tone(buzzer, 3000);
    delay(5000);
    digitalWrite(ledPin, LOW);
    digitalWrite(pompaApa, LOW);
    noTone(buzzer);
    DHT.read11(tempSenzorPin);
    temperaturaCamera = DHT.temperature;
    display.clearDisplay();
    display.display();

    display.setCursor(0, 0);
    display.println("Temperatura ");
    display.print("camera: ");
    display.print(temperaturaCamera);
    display.print("C");
    display.print("Umiditate ");
    display.print("sol: ");
    display.print(valoareSenzorPamant);
    display.print("%");
  }

  delay(1000);
}
