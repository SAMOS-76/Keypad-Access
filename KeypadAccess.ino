#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
// include libraries
// const byte COLS = 4; //uncomment if using 4x4 keypad 
const byte COLS = 3;    //comment if using 4x4 keypad
const byte ROWS = 4;
/* uncomment if using 4x4 keypad 
char keys[ROWS][COLS] = 
  {{'1','2','3'},
   {'4','5','6'},
   {'7','8','9'},
   {'*','0','#'}}; */
// comment below out if using 4x4 keypad 
char keys[ROWS][COLS] = 
  {{'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}};
// Here I used the back pins of my Arduino mega so all the wires are in the same place
byte rowPins[ROWS]={25, 29, 33, 37}; // pins 1-4 on keypad
byte colPins[ROWS]={41, 45, 49};     // pins 5-7 on keypad
// Add another pin to colPins if using 4x4 keypad
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); // (rs, e, d4, d5, d6, d7)
// array size = length of pin
char pin[6] = {'1','2','3','4','5','6'}; // change the pin as you wish
char attempt[6] = {0,0,0,0,0,0}; // this array holds the values you just typed in and must be the same size as pin
int lenghtPin = 6; // this is the length of the pin. Size is the size of the pin
int z = 0; // holds the value of the number of buttons presses

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
  pinEnter();
}
void pinEnter(){ // This is the "starting screen"
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Pin");
}

void pinCorrect(){ // This is called if the pin is correct
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pin is correct");
  delay(1000);
  pinEnter(); // Goes back to the enter screen
  z = 0;
}
void pinIncorrect(){ // This is called if the pin is incorrect
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pin is incorrect");
  delay(1000);
  pinEnter(); // Goes back to the enter screen
  z = 0;
}

void checkPin(){
  int correct = 0;
  for(int i;i<lenghtPin;i++){
    if(attempt[i] == pin[i]){ // If the values you entered are the same as the pin then it is correct
      correct ++;
    }
  }
  if(correct == lenghtPin){
    pinCorrect();
  }else{
    pinIncorrect();
  }
  for(int zz=0;zz<lenghtPin;zz++){
    attempt[zz]=0;
  }
}
void readKeypad(){
  char Key = customKeypad.getKey(); // Gets the keys pressed on the keypad
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
