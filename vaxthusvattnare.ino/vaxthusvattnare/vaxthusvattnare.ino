#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// lägger til essentiella bibliotek för koden

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SSD1306_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//initierar skärmen och bredden

const int sensorPin = A0; //info för jordfuktighet
const int mangdavdata = 10; // hur många värden på fuktigheten som läses in i medelvärdet
int data[mangdavdata];
int indexiarray = 0; //annan variabel för att kunna byta ut värden i arrayen
int total = 0; // totala summan av värden i arrayen
int medelvarde = 0; // värdet på totalen / mangdavdata
const int pumpPin = 7; // ström av eller på för att regulera pumpen
//lägger till variablar

void setup() {
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    for (;;); // kontrollerar att display initierats korrekt
  }
  display.clearDisplay();
  for (int i = 0; i < mangdavdata; i++) { // fyller arrayen med nollor, dessa byts senare ut 
    data[i] = 0;
  }
} //penis
 
void loop() {
  int newReading = analogRead(sensorPin); //skapar en lokal variabel med det senaste värdet på fuktighetssesnorn
  total -= data[indexiarray]; //tar bort det äldsta värdet på plats 0 i arrayen
  data[indexiarray] = newReading; // skriver in det nya värdet på rätt plats
  total += newReading; //lägger till variabeln med det senaste värdet i arrayen för att uppdatera summan
  indexiarray = (indexiarray + 1) % mangdavdata; // flyttar indexet till nästa plats i arrayen samt ser till att det loopas
  medelvarde = total / mangdavdata; // delar total sum med mangdavdata för att skapa ett medelvärde
  Serial.print("Jordfuktighet (medelvärde): ");
  Serial.println(medelvarde); // serial monitor kod
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0); // förberedelser för att skriva text på oled skärmen
  if (medelvarde > 930) {
    display.println("very torrt!");
          for (int i = 0; i < 12; i++); { // skapar en for-loop med tolv inkrement
            digitalWrite(pumpPin, HIGH);
            delay (300);
            digitalWrite(pumpPin, LOW);
            delay(300); }} //om jordfuktigheten är över 930 anses det väldigt torrt och den vattnar 12 gånger med en delay på 300ms
            if (930 > medelvarde > 500){
              display.println("lite torrt!");
              for (int i = 0; i < 8; i++);{
                digitalWrite(pumpPin, HIGH);
                delay(600);
                digitalWrite(pumpPin, LOW);
                delay(600); // om jordfuktigheten är under 930, men mer än 500 så vattnar den åtta gånger med en delay på 600ms
              }}
              if (500 > medelvarde > 200){
                display.println("ganska wet!");
                for (int i = 0; i < 4; i++);{
                  digitalWrite(pumpPin, HIGH);
                  delay(1000);
                  digitalWrite(pumpPin, LOW);
                  delay(1000); // pumppin aktiveras på och av med en delay på en sekund, endast fyra gånger
                }
              }
              if (200 > medelvarde > 0){
                display.println("mycket wet!"); // om fuktigheten i jorden är 200 eller under så är det optmalt och krävs inget vattnande 
              }
            
  display.display();
  delay(500); // lägger till en delay för loopen
}
