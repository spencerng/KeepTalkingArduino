#include<LiquidCrystal.h>

// Directives for LCD Buttons
#define btnSELECT 1
#define btnNONE   2

LiquidCrystal lcd(8,9,4,5,6,7);
int lcd_key = 0;
int adc_key_in = 0;
bool wasPressed = false;
bool isPressed2 = false;
int startTime, endTime, timeDiff;

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

 if (adc_key_in < 850)  {
  wasPressed = true;
  startTime = millis(); // start time diff
  return btnSELECT;
 }
 return btnNONE;
}

void setup() {
  Serial.begin(9600);
  // Replace 0 with an unconnected pin if necessary
  randomSeed(analogRead(0));
  int randWordIdx = random(4);
  int randColorIdx = random(4);
  int randStripe = random(4);
  lcd.begin(16,2);
  lcd.setCursor(4,0);
  lcd.println(words[randWordIdx]);
}

void loop() {
  read_LCD_buttons();
  adc_key_in = analogRead(0);
  // Check if button is being held
  while(adc_key_in < 850) { // while button pressed
   adc_key_in = analogRead(0);
   isPressed2 = true;
   if (adc_key_in > 1000) { // released
    endTime = millis();
    timeDiff = endTime - startTime;
    Serial.println(timeDiff);
    break;
   }
  }
}
