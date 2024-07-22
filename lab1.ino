//https://wokwi.com/projects/376034534469872641
#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

#define LIT_SPACE 0b00000000
#define LIT_T SEG_D | SEG_E | SEG_G | SEG_F
#define LIT_R SEG_E | SEG_G
#define LIT_A SEG_A | SEG_B | SEG_C  | SEG_E | SEG_F |  SEG_G
#define LIT_I SEG_C
#define LIT_N SEG_C | SEG_E | SEG_G
#define LIT_L SEG_D | SEG_E | SEG_F
#define LIT_E SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
#define LIT_F SEG_A | SEG_E | SEG_F |  SEG_G
const uint8_t SEG_RUNSTR[] = {
  LIT_T, LIT_R, LIT_A, LIT_I, LIT_N, LIT_SPACE,
  LIT_L, LIT_E, LIT_F, LIT_T, LIT_SPACE, 
  LIT_SPACE, LIT_SPACE, LIT_SPACE 
  };
const uint8_t MIN[] = {SEG_G};

TM1637Display display(CLK, DIO);

void setup()
{
}

void kim1_4(){
  for(int k = 100; k > 0; k-=2){
    display.showNumberDec(k, true); 
    delay(100);
  }
  display.clear();
  display.setSegments(MIN);
  for(int k=0; k <= 100; k+=2) {
    display.showNumberDecEx(k, 0b01000000, true, 3, 1);
    delay(100);
  }
  
}

void kim2_1(){
  display.setSegments(MIN);
  for(int k=200; k > 0; k-=20) { 
    display.showNumberDecEx(k, 0b10000000, true, 3, 1);
    delay(100);
  }
  
  display.clear();
  for(int k=0; k <= 200; k+=20) {
    display.showNumberDecEx(k, 0b10000000, true, 3, 1);
    delay(100);
  }
}

void kim3_4(){
  int k = 0;
  while(1){
      display.setSegments(SEG_RUNSTR+(k%12), 4, 0);
      k = (k+1)%12;
      delay(400);
  }
}

void loop()
{
  display.setBrightness(3);
  kim1_4();
  display.clear();
  kim2_1();
  display.clear();
  kim3_4();
  display.clear();
}
