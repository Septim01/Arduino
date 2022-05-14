#include "funshield.h"

constexpr int buttons[] = {button1_pin, button2_pin, button3_pin};
constexpr int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

bool prevpres[buttonCount] = {false, false, false};
int counter = 0;
int pos = 3;

constexpr int counterMax = 10000;
constexpr int segmentCount = 4;
constexpr int decimal_base = 10;


void updateSegment(byte mask, byte pos) {
  shiftOut(data_pin, clock_pin, MSBFIRST, mask);
  shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[pos]);
  digitalWrite(latch_pin, LOW);
  digitalWrite(latch_pin, HIGH);
}


int power(int exponent, int number){
  int value = 1;
  for(int i = 0; i < exponent; i++){
    value *= number;
    }
    return value;
  }


void increase(){
  counter += power(segmentCount-1-pos, decimal_base); 
  
  
  }
void decrease(){
  counter -= power(segmentCount-1-pos, decimal_base);
  
  }

void change(){
  pos--;
  pos = (pos + segmentCount) % segmentCount;
  }

void(*buttonFunctions[buttonCount])(void) = {increase, decrease, change};


int get_digit(){
  counter = (counter + counterMax) % counterMax ;
  int tmp = counter;
  for(int i = 0; i < segmentCount-1-pos; i++){
    tmp /= decimal_base;
  }
  return (tmp) % decimal_base;
}

void read_buttons(){
  for(int i = 0; i < buttonCount; i++){
    bool pressed = !digitalRead(buttons[i]);
    if(pressed && !prevpres[i]){
      buttonFunctions[i]();
    
  }
  prevpres[i] = pressed;  
 }
}
void setup() 
  {
  // put your setup code here, to run once:
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT); 
  pinMode(latch_pin, OUTPUT); 
  
  for (auto button : buttons)
    {
      pinMode(button, INPUT);
    }  
  }


void loop() {
  byte massk = digits[get_digit()];
  updateSegment(massk ,pos);

  read_buttons();
}
