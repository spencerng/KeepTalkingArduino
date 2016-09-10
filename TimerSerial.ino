
#include <TimeLib.h>

  
#include <LiquidCrystal.h>

#define IS_VOWEL_PIN 0
#define IS_ODD_PIN 1
#define STRIKE_PIN 3
   

 
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
int totalTime=300;



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

bool hasVowel(String serialNum){
  for(int i = 0; i<6;i++)
    if(serialNum.charAt(i)=='A'||serialNum.charAt(i)=='E'||serialNum.charAt(i)=='I'||serialNum.charAt(i)=='O'||serialNum.charAt(i)=='U')
      return true;
    return false;
 
}

bool isOdd(String serialNum){
  if(serialNum[5]=='1'||serialNum[5]=='3'||serialNum[5]=='5'||serialNum[5]=='7'||serialNum[5]=='9')
    return true;
   return false;
 
}

String generateSerial(){
  
 randomSeed(analogRead(2)); 
  char serialOptions[36];
  for(int i = 0; i < 36; i++){
    if(i>=26)
      serialOptions[i]=i+22;
    else serialOptions[i]=i+65;
  }
 
  String serialNum = "";
  for(int i = 0; i < 5; i++)
    serialNum+=serialOptions[random()%36];


  serialNum+=String(random()%10);

  return serialNum;
   
}

String serialNum;
void setup()
{
   setTime(14,17,0,10,9,2016); 
  
 lcd.begin(16, 2);
 pinMode(IS_ODD_PIN, OUTPUT);
 pinMode(IS_VOWEL_PIN, OUTPUT);
 
 serialNum = generateSerial();
 
 while(millis()/1000<=totalTime){
  lcd.setCursor(0,0); 
  lcd.print(getTime());
  lcd.setCursor(0,1);
  lcd.print(String("Serial #: ") + String(serialNum));
  delay(100);
  if(digitalRead(STRIKE_PIN))
    break;
    
 }
 lcd.setCursor(0,0); 
 if(digitalRead(STRIKE_PIN))
  lcd.print(getTime());
 else lcd.print("0.00   ");
 
 lcd.print("Game Over   ");
 lcd.setCursor(0,1);
 lcd.print(String("Serial #: ") + String(serialNum));
 
 
}
  
void loop()
{
  if(hasVowel(serialNum))
    digitalWrite(IS_VOWEL_PIN,HIGH);
  if(isOdd(serialNum))
    digitalWrite(IS_ODD_PIN,HIGH);  

}
