#define PASS_M 1 //A 
#define PASS_L 2 //B
#define BUT_M 3 //C
#define BUT_L 4  //D
#define SIMON_M 5 //E - swp w/ button
#define SIMON_L 6 //F
#define STRIKE1 7 
#define STRIKE2 8 
#define STRIKE3 9

bool isOn[6];
void setup() {
  for(int i = 0; i < 6; i++)
    isOn[i]=false;
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  
}

void signalListen(){
  for(int i=1;i<=4;i++)
    isOn[i]=digitalRead(i);
      


    
}

void updateStrikes(){
  for(int i=0;i<6;i++)
    if(isOn[i]){
      digitalWrite(9, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
    }
  if(isOn[4]||isOn[2]||isOn[0]||(isOn[3]&&isOn[5])||(isOn[1]&&isOn[5])||(isOn[1]&&isOn[3])){
    
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
  }
    
  if((isOn[4]&&isOn[5])||(isOn[3]&&isOn[4])||(isOn[2]&&isOn[5])||(isOn[2]&&isOn[3])||(isOn[1]&&isOn[4])||(isOn[1]&&isOn[2])||(isOn[0]&&isOn[5])||(isOn[0]&&isOn[4])||(isOn[0]&&isOn[3])||(isOn[0]&&isOn[2])||(isOn[0]&&isOn[1])||(isOn[1]&&isOn[2]&&isOn[5]));{
    
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
  }
    
}

void loop() {
  signalListen();
  updateStrikes();
  
}
