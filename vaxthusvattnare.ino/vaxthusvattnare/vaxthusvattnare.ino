#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SSD1306_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int sensorPin = A0;
const int mangdavdata = 10;
int data[mangdavdata];
int indexiarray = 0;
int total = 0;
int medelvarde = 0;
const int pumpPin = 7;

void setup() {
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    for (;;);
  }
  display.clearDisplay();
  for (int i = 0; i < mangdavdata; i++) {
    data[i] = 0;
  }
} //penis
 
void loop() {
  int newReading = analogRead(sensorPin);
  total -= data[indexiarray];
  data[indexiarray] = newReading;
  total += newReading;
  indexiarray = (indexiarray + 1) % mangdavdata;
  medelvarde = total / mangdavdata;
  Serial.print("Jordfuktighet (medelvärde): ");
  Serial.println(medelvarde);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  if (medelvarde > 930) {
    display.println("very torrt!");
          for (int i = 0; i < 12; i++); {
            digitalWrite(pumpPin, HIGH);
            delay (300);
            digitalWrite(pumpPin, LOW);
            delay(300); }}
            if (930 > medelvarde > 500){
              display.println("lite torrt!");
              for (int i = 0; i < 12; i++);{
                digitalWrite(pumpPin, HIGH);
                delay(600);
                digitalWrite(pumpPin, LOW);
                delay(600);
              }}
              if (500 > )
            }
  display.display();
  delay(500);
}
