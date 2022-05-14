#include "funshield.h"

unsigned long last_time = 0;
unsigned int state = 0;
constexpr int program_size = 4;
unsigned int program[program_size] = {led1_pin,led2_pin,led3_pin,led4_pin};
unsigned long period = 300;
bool t_f = true;


void setup()
{
  for(int i = 0; i < program_size; i++)
  {
    pinMode(program[i], OUTPUT);
    digitalWrite(program[i], OFF);
  }
}


void turn_led(int i_on)
  {
    for (int i=0; i<program_size; i++)
    {
        digitalWrite(program[i], OFF);
        
    }
    digitalWrite(program[i_on], ON);
}
   
void changeState() {
    if (t_f){
        state++;
    } else {
        state--;
    }
    if (state == 0 or state == program_size - 1) {
        t_f = !t_f;
    }
}
      

void loop()
  {
    unsigned long time_now = millis();
    if(time_now - last_time >= period)
    {
        turn_led(state);
        changeState();
        last_time = millis();
    }
    
  }
