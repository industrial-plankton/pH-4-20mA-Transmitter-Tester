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


  pinMode(PWM_out_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Blink for power/run indication
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
}

void loop() {
  const int sensorValue = analogRead(A7);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  const int pH = map(sensorValue, (1023 * 0.6 / 5), (1023 * 3 / 5), 0, 1400);  // using a 150 ohm resistor, so 20 mA maps to a max of 3 V

    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print(pH);
    lcd.setCursor(0, 1);
    if (pH >= 450 && pH <= 550) {
      lcd.print("good");
    } else {
      lcd.print("bad");
    }

    delay(1400);
}
