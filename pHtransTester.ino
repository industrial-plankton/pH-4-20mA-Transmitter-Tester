#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h> // https://github.com/mathertel/LiquidCrystal_PCF8574

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2);  // initialize the lcd


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Blink for power/run indication
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
}

void loop() {
  const int sensorValue = analogRead(A7);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
const float resistance = 80; // This changes, for some reason the inrush 4-20 adds a resistance to the pin and it changes every time
const float LowVoltage = 0.004 * resistance;
const float HighVoltage = 0.020 * resistance;

  const int pH = map(sensorValue, ((1023 * LowVoltage) / 5), ((1023 * HighVoltage) / 5), 0, 1400);  // using a 150 ohm resistor, so 4-20 mA maps to 0.6-3 V // ~60 ohm now so 0.24-1.2V
  const int milivolts = map(sensorValue, 0, 1023, 0, 5000);

    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print(pH);
    lcd.print(" : ");
    lcd.print(sensorValue);
    lcd.print(" : ");
    lcd.print(milivolts);
    lcd.print(" mV");
    lcd.setCursor(0, 1);
    if (pH >= 250 && pH <= 550) {
      lcd.print("good");
    } else {
      lcd.print("bad");
    }

    delay(1400);
}
