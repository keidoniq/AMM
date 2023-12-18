//https://wokwi.com/projects/384202754168672257

#define nRows 4
#define nCols 4
#define ui uint8_t 

class matrixKeypad {
    char key[nRows][nCols];
    ui rPins[nRows], cPins[nCols];

    void cpArray(ui size, char* source, char* dest){
        for(ui i = 0; i < size; ++i)
          dest[i] = source[i];
    }

public:
    matrixKeypad(char userKey[nRows][nCols], ui userRpin[nRows], ui userCpin[nCols]);
    char getKey();
};

matrixKeypad::matrixKeypad(char userKey[nRows][nCols], ui userRpin[nRows], ui userCpin[nCols]){
  for (ui i = 0; i < nRows; ++i) {
        cpArray(nCols, userKey[i], key[i]);
        rPins[i] = userRpin[i];
        cPins[i] = userCpin[i];
  }

  //nRows == nCols == 4 -> it could be the same cycle 
  for (ui i = 0; i < nCols/*== nRows*/; ++i) {
        pinMode(cPins[i], OUTPUT); 
        digitalWrite(cPins[i], LOW);
        pinMode(rPins[i], INPUT_PULLUP);
  }
}

char matrixKeypad::getKey(){

      char ch = '\0';
      
      for (ui col = 0; col < nCols; ++col) {
      pinMode(cPins[col], OUTPUT);
        digitalWrite(cPins[col], LOW);
        for (ui row = 0; row < nRows; ++row) {
            pinMode(rPins[row], INPUT_PULLUP);
            delay(10);
            if (digitalRead(rPins[row]) == LOW) {
              delay(10);
              if (digitalRead(rPins[row]) == LOW) {

                pinMode(cPins[col], INPUT_PULLUP);
                ch = key[row][col];
                delay(50);
                
                //Serial.print("key: ");
                //Serial.print(ch);
              }
            }
            pinMode(rPins[row], OUTPUT);
            digitalWrite(rPins[row], LOW);
        }
        pinMode(cPins[col], INPUT_PULLUP);
      }
      return ch;
  }

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


// interpretate:
//   A -> go to next 
//   B -> go back
//   D -> do curr choice
//  
// menu choices:
// 1:
//   [0;9] -> continue write to var variable
//   # -> put to memory
//   A -> write to another variable
//   D -> do calculation
//   C -> clear values
//   B -> storage value back from memory
//   * -> exit to menu
// 2:
//   -
// 3:
//   /*clear memory??*/
//   A -> yes
//   B -> no
//   * -> exit to menu
//
// savedValue:
//   which variable save?
//   A -> x
//   B -> y
//   C -> z
//   D -> acceptance, "done"
//


char keypadKey[nRows][nCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
ui rPins[nRows]  = {2, 3, 4, 8};
ui cPins[nCols] = {7, 6, 5, 19}; 

matrixKeypad keypad(keypadKey, rPins, cPins);
LiquidCrystal_I2C lcd(0x27, 2, 16);

//operands x, y
//result in z

int x, y, z;
int storagedData = 0;
int choice = 1;
char intrpt = 'D';
const ui interruPin = cPins[3];
bool wasInterrupted = true;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  EEPROM.get(0, storagedData);
  attachInterrupt(digitalPinToInterrupt(interruPin), reacToInterrupt, FALLING);
  showMenu();
}


void loop() {
  
 /// Serial.println("before loop:" + String(wasInterrupted));
  if(wasInterrupted){
  Serial.print("loop!!");
  //
  //  Serial.print("in interpretate ");
  //  Serial.print(intrpt);
  switch (intrpt) {
    case 'D':
        if(choice == 2){
          //lcd.clear();
          //Serial.println("choice 2");
          //lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("memory:"); 
          lcd.print(storagedData);
        }
        else if(choice == 1){
          //Serial.println("choice 1");
          choice1();
        }
        else if(choice == 3){
          //Serial.println("choice 3");
          choice3();
        }
        showMenu();
        //wasInterrupted = false;
        break;
      case 'B':
        //Serial.println("intr B");
        choice = (choice-1) % 3;
        if(!choice)
          choice = 3;
        //1 - 1 = 0, 2-1=1, 3-1 = 2
        showMenu();
       // delay(100);
       // wasInterrupted = false;
        break;
     case 'A':
        //Serial.println("intr A");
        //1 + 1 = 2, 2+1=0, 3+1 = 1
        choice = (choice+1) % 3;
        if(!choice)
          choice = 3;
          
        showMenu();
        //delay(100);
        //wasInterrupted = false;
        break;
    }
    intrpt = ' ';
    wasInterrupted = false;
  }
}


void showMenu() 
{
  
  Serial.println("show menu");
  lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print(choice);
  //lcd.setCursor(0, 1);
  
  switch (choice) {
      case 1:
        Serial.println("calculate");
        lcd.setCursor(0, 0);
        lcd.print("1");
        lcd.setCursor(0, 1);
        lcd.print("calculate");
        reacToInterrupt();
        break;
      case 2:
        Serial.println("memory");
        lcd.setCursor(0, 0);
        lcd.print("2");
        lcd.setCursor(0, 1);
        lcd.print("memory:"); 
        lcd.print(storagedData);
        reacToInterrupt();
        break;
      case 3:
        Serial.println("clear memory");
        lcd.setCursor(0, 0);
        lcd.print("3");
        lcd.setCursor(0, 1);
        lcd.print("clear memory");
        reacToInterrupt();
        break;
  }

}

void reacToInterrupt() {
  Serial.println(wasInterrupted);
  if(!wasInterrupted){
    wasInterrupted = true;
    Serial.print("interrupt!!");
    intrpt = keypad.getKey();
    Serial.println(intrpt);
    //interpretate();//showMenu();
  }
}




void choice1() 
{
  //Serial.println("in choice1");
  char nextKey = ' ';
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("calculator:");
  while(nextKey != '*')
  {
    detachInterrupt(digitalPinToInterrupt(interruPin));
    nextKey = keypad.getKey(); 
    attachInterrupt(digitalPinToInterrupt(interruPin), reacToInterrupt, FALLING);
    //Serial.print(nextKey);
    switch (nextKey) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        x = x * 10 + (nextKey - '0');
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("value = ");
        lcd.print(x);
        Serial.print("->");
        Serial.println(x);
        break;
      case '#':
        {int tryToSave = savedValue();
        if(tryToSave >= 0){
          storagedData = tryToSave;
          EEPROM.update(9, storagedData); // <=> storegedData was changed
          //Serial.println("data was saved.");
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print(String(storagedData) +" was saved.");
        }
        else{
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("nothing was saved.");
        }
        break;
        }        
      case 'D':
        z = x ^ y;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(y);
        lcd.print(" xor ");
        lcd.print(x);
        lcd.setCursor(0, 1);
        lcd.print(" = ");
        lcd.print(z);
        delay(100);
        break;
       case 'B':
        x = storagedData < 0 ? 0:storagedData;
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("value = ");
        lcd.print(x);
        break;
      case 'C':
        lcd.clear();
        lcd.setCursor(0, 0);
        clearValues();
        lcd.print("current values");
        lcd.setCursor(0, 1);
        lcd.print("were deleted.");
        delay(100);
        break;
      case 'A':
      {
        int tmp = x;
        x = y;
        y = tmp;
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("value = ");
        break;
      }
    }
  }
  clearValues();
  intrpt = '\0';
}

void choice3() 
{
    //Serial.println("in choice3");
    char nextKey = ' ';
    detachInterrupt(digitalPinToInterrupt(interruPin));
    nextKey = keypad.getKey(); 
    attachInterrupt(digitalPinToInterrupt(interruPin), reacToInterrupt, FALLING);
    //Serial.println(nextKey);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Clear memory??");
    lcd.setCursor(0, 1);
    lcd.print("A - yes, B - no.");
    while(nextKey != '*')
    {
      nextKey = keypad.getKey();
      if (nextKey == 'A'){
        EEPROM.update(0, 255);
        storagedData = 0;
        
        lcd.setCursor(0, 0);
        lcd.print("memory cleared.");
        //Serial.println("choice3, memory was cleared.");lcd.setCursor(0, 1);
        lcd.print("press * for exit.");
        delay(1000);
      }
      else if (nextKey == 'B'){
        lcd.setCursor(0, 0);
        lcd.print("nothing changed.");
        //Serial.println("choice3, nothing was done.");
        lcd.setCursor(0, 1);
        lcd.print("press * for exit.");
        delay(1000);
      } 
    
  }
  intrpt = '\0';
}

int savedValue(){
  int valueToSave = -1, tmp;
  char nextKey = ' ';
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("x, y, z = ");
  lcd.setCursor(0, 1); 
  lcd.print(String(y) + "," + String(x) + ","  + String(z));
  while(nextKey != 'D' && nextKey != '*')
  {
    detachInterrupt(digitalPinToInterrupt(interruPin));
    nextKey = keypad.getKey(); 
    attachInterrupt(digitalPinToInterrupt(interruPin), reacToInterrupt, FALLING);
    //Serial.print(nextKey);
    switch (nextKey) {
      case 'A':
        lcd.setCursor(0, 0);
        lcd.print("save x = " + String(y) + "??");
        tmp = y;
        break;
      case 'B':
        lcd.setCursor(0, 0);
        lcd.print("save y = " + String(x) + "??");
        tmp = x;
        break;
      case 'C':
        lcd.setCursor(0, 0);
        lcd.print("save z = " + String(z) + "??");
        tmp = z;
        break;
      
    }
  }
  return (nextKey == '*' ? valueToSave:tmp);
}

void clearValues(){
  z = 0;
  x = 0;
  y = 0;
}
