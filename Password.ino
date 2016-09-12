//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
 
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}
String wordList[]={"ABOUT","AFTER","AGAIN","BELOW","COULD","EVERY","FIRST","FOUND","GREAT","HOUSE","LARGE","LEARN","NEVER","OTHER","PLACE","PLANT","POINT","RIGHT","SMALL","SOUND","SPELL","STILL","STUDY","THEIR","THERE","THESE","THING","THINK","THREE","WATER","WHERE","WHICH","WOULD","WRITE"};
String generateWord(){
  
  return wordList[random()%35];
  
}

String answer;
char choices[5][7];
int currentSelection[5];
int cursorPos = 0;

void displayWord(){
  String currentDisplay =" ";
  for(int i = 0; i<5; i++)
    currentDisplay+= String(choices[i][currentSelection[i]])+"  ";
  lcd.print(currentDisplay);
  
}


 
void setup()
{
  randomSeed(analogRead(2));
  answer=generateWord();
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 for(int i = 0; i < 5; i++){
  choices[i][0]=answer[i];
  for(int j = 1; j<7;j++){
    
    choices[i][j]=random(26)+65;
    for(int k=0;k<j;k++)
      if(choices[i][k]==choices[i][j])
        j--;

  }
  
  
  
 }

 for(int i = 0; i < 5; i++)
  currentSelection[i]=random(7);
 


}

void displayData(){
 lcd.setCursor(0,0);
 displayWord();
 lcd.setCursor(0,1);
 if(cursorPos==0)
  lcd.print(" _");
  if(cursorPos==1)
  lcd.print("    _");
  if(cursorPos==2)
  lcd.print("       _");
  if(cursorPos==3)
  lcd.print("          _");
  if(cursorPos==4)
  lcd.print("             _");
 
}


 bool isCorrect(){
  String currentWord="";
  
  for(int i = 0; i< 5; i++)
    currentWord+=String(choices[i][currentSelection[i]]);
  
  for(int i = 0;i<35;i++)
    if(wordList[i].equals(currentWord))
      return true;
  return false;  
 }

  
void loop()
{

  displayData();
 
          
 lcd_key = read_LCD_buttons();  // read the buttons

 
 
 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
      
     
      
     
     if(++cursorPos==5){
      cursorPos=0;
      lcd.clear();
     }
     break;
     }
   case btnLEFT:
     {
      
      if(--cursorPos==-1){
      cursorPos=4;
     
      }
      lcd.clear();
      
     break;
     }
   case btnUP:
     {
     if(++currentSelection[cursorPos]==7)
      currentSelection[cursorPos]=0;
     break;
     }
   case btnDOWN:
     {
      if(--currentSelection[cursorPos]==-1)
      currentSelection[cursorPos]=6;
     
     break;
     }
   case btnSELECT:
     {
      lcd.clear();
     if (isCorrect()){
      
      lcd.print("YOU WIN");
      
     }
     else{
      
      lcd.print("YOU LOSE");
     }
     delay(10000000);
     break;
     
     }
     case btnNONE:
     {
        
     
     
     break;
     }
     
 }
 delay(100);

 
}



