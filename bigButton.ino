#include<LiquidCrystal.h>

// Directives for LCD Buttons
#define btnSELECT 1
#define btnNONE   2

LiquidCrystal lcd(8,9,4,5,6,7);
int lcd_key = 0;
int adc_key_in = 0;
int totalTime=300;
bool wasPressed = false;
bool isPressed2 = false;
int startTime, endTime, timeDiff;
int mistakeCount;
int randWordIdx = random(4);  // Gets button word
int randColorIdx = random(4); // Gets color of button
int randStripe;
String gameTime;

String getTime(){
 lcd.clear();
 int secLeft = totalTime - (millis()/1000);
 int minLeft = 0;
 while(secLeft>=60){
  minLeft++;
  secLeft-=60;
 }

 if(!minLeft){
    String millsLeft = String(millis());
    if(millsLeft.length()==4)
      return String(secLeft) + '.' + millsLeft.charAt(1)+millsLeft.charAt(2);
    else return String(secLeft) + '.' + millsLeft.charAt(2)+millsLeft.charAt(3);

 }
 return String(minLeft) + ':'+ (secLeft >= 10 ? String(secLeft) : String("0" + String(secLeft)));
}

// Used for both button bg & stripes
String colors[4] = {
  "purple",
  "green",
  "red",
  "blue"
};

String words[4] = {
  "ABORT       ", // 7 spaces
  "DETONATE    ", // 4 Spaces
  "HOLD        ", // 8 spaces
  "PRESS       "  // 7 spaces
};

// read the buttons
int read_LCD_buttons() {
 adc_key_in = analogRead(0); // read the value from the sensor
 // we add approx 50 to those values and check to see if we are close

 if (adc_key_in < 850)  {
  randStripe = random(4);
  wasPressed = true;
  startTime = millis(); // start time diff
  return btnSELECT;
 }
 return btnNONE;
}

/*
void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(1500);
  digitalWrite(pin, LOW);
}

void changeStripe(String color, int pin) {
  if (color == "green") // blinkLED(GREEN_PIN);
  else if (color == "red") // blinkLED(RED_PIN);
  else if (color == "blue") // blinkLED(BLUE_PIN);
  else { // purple
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
    delay(1500);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
  }
}
*/

bool inArray(char arr[], char number) {
  for (int i = 0; i < 9; i++) {
    if (arr[i] == number) return true;
    else return false;
  }
}

bool isCorrectMove(String buttonColor, String stripeColor, String buttonText, String gTime, int releaseTime) {
  char gameTimeNumbers[7];
  for (int i = 0; i < gTime.length(); i++) gameTimeNumbers[i] = gTime[i];
  Serial.println(gTime);
  for (int i = 0; i < 7; i++) Serial.println(gameTimeNumbers[i]);
  if (buttonColor == "blue" && buttonText == "ABORT" && stripeColor == "blue" && inArray(gameTimeNumbers, '4')) return true;
  else if (buttonColor == "blue" && buttonText == "ABORT" && (stripeColor == "purple" || stripeColor == "red") && inArray(gameTimeNumbers, '1')) return true;
  else if (buttonColor == "blue" && buttonText == "ABORT" && stripeColor == "green" && inArray(gameTimeNumbers, '5')) return true;
  else if (buttonColor == "green" && stripeColor == "blue" && inArray(gameTimeNumbers, '4') ) return true;
  else if (buttonColor == "green" && stripeColor == "green" && inArray(gameTimeNumbers, '5')) return true;
  else if (buttonColor == "green" && (stripeColor == "red" || stripeColor == "purple") && inArray(gameTimeNumbers, '1')) return true;
  else if (buttonColor == "red" && buttonText == "HOLD" && releaseTime < 1000) return true;
  // Bullet 7 of Page 6 of Manual v.1
  else if (stripeColor == "blue" && inArray(gameTimeNumbers, '4')) return true;
  else if ((stripeColor == "purple" || stripeColor == "red") && inArray(gameTimeNumbers, '1')) return true;
  else if (stripeColor == "green" && inArray(gameTimeNumbers, '5')) return true;
  return false;
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // button color
  digitalWrite(13, 250);
  //pinMode(PIN, OUTPUT); // stripe
  // Replace 0 with an unconnected pin if necessary
  randomSeed(analogRead(0));
  lcd.begin(16,2);
  lcd.setCursor(4,0);
  lcd.println("DETONATE    "); //lcd.println(words[randWordIdx]);
}

void loop() {
  digitalWrite(13, 255);
  read_LCD_buttons();
  adc_key_in = analogRead(0);
  // Check if button is being held
  while(adc_key_in < 850) { // while button pressed
   adc_key_in = analogRead(0);
   isPressed2 = true;
   if (adc_key_in > 1000) { // released
    endTime = millis();
    timeDiff = endTime - startTime;
    gameTime = getTime();
    Serial.println(colors[randColorIdx]);
    Serial.println(colors[randStripe]);
    Serial.println(words[randWordIdx]);
    Serial.println(gameTime);
    Serial.println(timeDiff);

    bool endGame = isCorrectMove(colors[randColorIdx], colors[randStripe], words[randWordIdx], gameTime, timeDiff);
    if (endGame) {
      digitalWrite(13, 250);
      //digitalWrite(VICTORY_PIN, HIGH);
      lcd.println("You winnn");
      while(1) {}
    } else {
      mistakeCount+=1;
      if (mistakeCount >= 3)  {
        lcd.println("U losseeedd");
        //digitalWrite(LOSS_PIN, HIGH);
        while(1) {}
      }
    }
    break;
   }
  }
}
