#include "funshield.h"

constexpr int buttons[] = {button1_pin, button2_pin, button3_pin};
constexpr int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

bool prevpres[buttonCount] = {false, false, false};
int pos = 3;
bool frozen_running = false;
bool frozen = true;

constexpr int segmentCount = 4;
constexpr int base = 10;
constexpr int lenght_digit = 4;

unsigned long curr_time_stopped = 0;
unsigned long interval = 0;

constexpr int to_seconds = 100;
constexpr int second_digit = 2;
constexpr int get_two_digits = 99;
constexpr int last_position = 3;


void updateSegment(byte mask, byte pos) {
  shiftOut(data_pin, clock_pin, MSBFIRST, mask);
  shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[pos]);
  digitalWrite(latch_pin, LOW);
  digitalWrite(latch_pin, HIGH);
}


void freeze(unsigned long number){
  if(frozen_running){
    return;
  }
  if(frozen && !frozen_running){
    interval += number - curr_time_stopped;
    }
  frozen = !frozen;
  curr_time_stopped = number;
  }
  
void freeze_running(unsigned long number){
  if(!frozen){
    curr_time_stopped = number;
    frozen_running = !frozen_running;
    }
  }

void reset(unsigned long number){
  if(frozen && !frozen_running){
    interval = curr_time_stopped;
  }
}

int one_by_one(int number,int pos){
  int tmp;
  for(int i = 0; i < last_position-pos; i++){
    number /= base;
  }
  tmp = number % base;
  return tmp;
}

void(*buttonFunctions[buttonCount])(unsigned long) = {freeze, freeze_running, reset};

int get_int_len(int value);

void get_digits(unsigned long int number){
  number /= to_seconds;
  int len_digits = get_int_len(number);
  int digit = one_by_one(number, pos);
  (pos == second_digit) ? updateSegment(digits[digit] & 0x7f, pos) : updateSegment(digits[digit], pos);
  pos--;
  if(pos < segmentCount-len_digits){
    pos = 3;
    }
  
}

void read_buttons(unsigned long curr_time){
  for(int i = 0; i < buttonCount; i++){
    bool pressed = !digitalRead(buttons[i]);
    if(pressed && !prevpres[i]){
      buttonFunctions[i](curr_time);
    
  }
  prevpres[i] = pressed;  
 }
}

int get_int_len (int value){
  int i=2;
  while(value > get_two_digits){ i++; value /=10; }
  return i;
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
    unsigned long curr_time = millis();    
    read_buttons(curr_time);
    if(frozen_running || frozen){  
      get_digits(curr_time_stopped - interval);
}

    else{
      get_digits(curr_time - interval);
}
    
}
