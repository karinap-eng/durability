#include <LiquidCrystal.h>
#include <Keypad.h>

long int evaluateInput(int array[]);
long int userInput(int array[]);
void motor(long int distance, long int cycles, long int speed);

const int maxDistance = 5;
const int maxCycles = 3;
const int maxSpeed = 5;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define PUL 5
#define DIR 4
#define ENABLE 3

const byte ROWS = 4;
const byte COLS = 4;

char keypads[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[COLS] = {31, 33, 35, 37};
byte rowPins[ROWS] = {39, 41, 43, 45};

Keypad Keypd = Keypad(makeKeymap(keypads), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(PUL, LOW);
  digitalWrite(DIR, LOW);
  digitalWrite(ENABLE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ENABLE, LOW);
  lcd.clear();
  int distanceInput[maxDistance];
  initializeArray(distanceInput, maxDistance);
  int cyclesInput[maxCycles];
  initializeArray(cyclesInput, maxCycles);
  int speedInput[maxSpeed];
  initializeArray(speedInput, maxSpeed);
  
  long int distance = 0;
  long int cycles = 0;
  long int speed = 0;
  
  int key = 0;
  
  lcd.setCursor(0,0);
  lcd.print("Enter Distance:");
  lcd.setCursor(0,1);
  distance = userInput(distanceInput, maxDistance);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter Cycles:");
  lcd.setCursor(0,1);
  cycles = userInput(cyclesInput, maxCycles);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter Speed:");
  lcd.setCursor(0,1);
  speed = userInput(speedInput, maxSpeed);
  lcd.clear();

  motor(distance, cycles, speed);
  
}

int initializeArray(int array[], int maxLimit){
  for(int i=0; i<maxLimit; i++){
    array[i] = 35;
  }
}
  
  long int userInput(int array[], int maxLimit){
    int i = 0;
    int key;
    
    while(true){
       key = 0;
       key = Keypd.getKey();
  
       if(key==42){
        //restart input, restart loop()
       }
       
       if(key==68){
        break;
       }
       if(key && i<maxLimit && key>=48 && key<=57){
         lcd.print(char(key));
         array[i] = key;
         i++; 
       }
    }
    return evaluateInput(array, maxLimit);
  }
  
  long int evaluateInput(int array[], int maxLimit){
    long int number = 0;
    
    for(int i=0; i<maxLimit; i++){
      if(array[i]==35){
        break;
      }
      number *= 10;
      number += (array[i]-48);
    }
    return number;
  }
  
  void motor(long int distance, long int cycles, long int speed){
    digitalWrite(ENABLE, HIGH);
    
    
    for(int i=0;i<cycles; i++){
      
      digitalWrite(DIR, LOW);         //CLOCKWISE
      for(int j=0; j<distance; j++){
        //rotate clockwise
        digitalWrite(PUL, HIGH);
        delayMicroseconds(speed);
        digitalWrite(PUL, LOW);
        delayMicroseconds(speed);
      }
      
      digitalWrite(DIR, HIGH);         //COUNTER CLOCKWISE
      for(int k=0; k<distance; k++){
        //rotate counter clockwise
        digitalWrite(PUL, HIGH);
        delayMicroseconds(speed);
        digitalWrite(PUL, LOW);
        delayMicroseconds(speed);
      }

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cycles Completed:");
      lcd.setCursor(0,1);
      lcd.print(i);
    }
    digitalWrite(ENABLE, LOW);
  }

  void clearCycles(){
    
  }

  void clearInput(){
    
  }

  
