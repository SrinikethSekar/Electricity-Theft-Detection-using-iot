#include"NewPing.h"

#include"Wire.h"

#include"LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
int seconds = 0;
const int moisturePin1 = A0;
#define TRIGGER_PIN D6
#define ECHO_PIN D7
const int buzzpin = D3;
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float tempval1;
float tempval2;
int finalval;
void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzpin, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int moistureValue = analogRead(moisturePin1);
  Serial.print("Moisture1 Value: ");
  Serial.println(moistureValue);
  if ((moistureValue <= 1000) || (finalval <= 40)) {
    digitalWrite(buzzpin, HIGH);
    delay(1000);
  } else {
    digitalWrite(buzzpin, LOW);
  }
  delay(20);
  Serial.print("Ping: ");
  int iterations = 10;
  tempval1 = ((sonar.ping_median(iterations) / 2) * 0.0343);
  if (tempval1 - tempval2 > 60 || tempval1 - tempval2 < -60) {
    tempval2 = (tempval1 * 0.02) + (tempval2 * 0.98);
  } else {
    tempval2 = (tempval1 * 0.4) + (tempval2 * 0.6);
  }
  finalval = tempval2;
  Serial.print(finalval);
  Serial.println("cm");
  lcd.setCursor(0, 0);
  lcd.print("finalval ");
  lcd.print(finalval);
}

