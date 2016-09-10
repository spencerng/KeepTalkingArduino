



#define GREEN 1
#define RED 2
#define BLUE 3
#define YELLOW 4


void flashColor(int color){
  
  if(color==GREEN){
    digitalWrite(A4,HIGH);
    delay(1500);
    digitalWrite(A4,LOW);
  }
  if(color==RED){
    digitalWrite(A5,HIGH);
    delay(1500);
    digitalWrite(A5,LOW);
  }
  if(color==YELLOW){
    digitalWrite(8,255);
    digitalWrite(9,255);
    delay(1500);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }

  if(color==BLUE){
    digitalWrite(11, HIGH);
    delay(1500);
    digitalWrite(11, LOW);
  }
  

}

int numberPassed = 3;

void flashColors(int seq[]){
  int size2 = numberPassed+1;
  for(int i = 0; i<size2;i++){
    flashColor(seq[i]);
    delay(250);
  }
  Serial.println("Iteration ended"); 
  delay(2000);
}




void setup() {
  pinMode(11,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
  randomSeed(analogRead(0));
  int colors[4];
  for(int i = 0; i < 4; i++)
    colors[i] = random(4);
  
  int alwaysOnPins[] = {1,3,5,9,12};
  for(int i = 0; i < 5; i++){
    pinMode(alwaysOnPins[i], OUTPUT);
    digitalWrite(alwaysOnPins[i], HIGH);
  }
  digitalWrite(A3,HIGH);
  
  
  
  while(numberPassed<4){
    int currentSequence[numberPassed+1];
    for(int i = 0; i<numberPassed+1;i++)
      currentSequence[i]=colors[i];
    flashColors(currentSequence);
    
  }
  

}


void loop() {

}
