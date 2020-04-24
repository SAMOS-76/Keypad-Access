#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte COLS = 4;
const byte ROWS = 4;

char keys[ROWS][COLS] = 
  {{'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}};
byte rowPins[ROWS]={25, 29, 33, 37};
byte colPins[ROWS]={41, 45, 49, 53};
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); // (rs, e, d4, d5, d6, d7)

char pin[6] = {'1','2','3','4','5','6'};
char attempt[6] = {0,0,0,0,0,0};
int z = 0;

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
  pinEnter();
}
void pinEnter(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Pin");
}

void pinCorrect(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pin is correct");
  delay(1000);
  pinEnter();
  z = 0;
}
void pinIncorrect(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pin is incorrect");
  delay(1000);
  pinEnter();
  z = 0;
}

void checkPin(){
  int correct = 0;
  for(int i;i<6;i++){
    if(attempt[i] == pin[i]){
      correct ++;
    }
  }
  if(correct == 6){
    pinCorrect();
  }else{
    pinIncorrect();
  }
  for(int zz=0;zz<6;zz++){
    attempt[zz]=0;
  }
}
void readKeypad(){
  char Key = customKeypad.getKey();
  if (Key!=NO_KEY){
    switch(Key){
      case '*':
        z=0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Pin");
        break;
      case '#':
        delay(100);
        checkPin();
        break;
      default:
        lcd.setCursor(z, 1);
        lcd.print("*");
        attempt[z]=Key;
        z++;        
    }
  }
}
void loop(){
  readKeypad();
}
