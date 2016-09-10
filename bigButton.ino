#include<LiquidCrystal.h>

// Directives for LCD Buttons
#define btnSELECT 1
#define btnNONE   2

LiquidCrystal lcd(8,9,4,5,6,7);
int lcd_key = 0;
int adc_key_in = 0;

// Used for both button bg & stripes
String colors[4] = {
  "white",
  "yellow",
  "red",
  "blue"
};

String words[4] = {
  "ABORT       ", // 7 spaces
  "DETONATE    ", // 4 Spaces
  "HOLD        ", // 8 spaces
  "PRESS       " // 7 spaces
};

// read the buttons
int read_LCD_buttons() {
 adc_key_in = analogRead(0); // read the value from the sensor
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 850)  return btnSELECT;
 return btnNONE;
}

// Check if button is being held


void setup() {
  Serial.begin(9600);
  // Replace 0 with an unconnected pin if necessary
  randomSeed(analogRead(0));
  lcd.begin(16,2);
  lcd.setCursor(4,0);
  int randWordIdx = random(4);
  lcd.println(words[randWordIdx]);
}

void loop() {
  lcd_key = read_LCD_buttons();
  switch (lcd_key) {
     case btnSELECT:
     {
       lcd.println("SELECT");
       break;
     }
     case btnNONE:
     {
       lcd.println("NONE  ");
       break;
     }
  }
}
