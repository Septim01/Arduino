#include "funshield.h"

constexpr int leds[] = {led1_pin, led2_pin, led3_pin, led4_pin};
constexpr int ledCount = sizeof(leds) / sizeof(leds[0]);

constexpr int buttons[] = {button1_pin, button2_pin};
constexpr int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

bool prevpres[buttonCount] = {false, false};
int count = 0;

constexpr unsigned wait_on = 300;
constexpr unsigned wait_off = 1000;

unsigned long timer = 0;
unsigned long timer2 = 0;  
bool activated[] = {false, false};



void turn_on_off(int number){
  number = (number) % 16;
  int bit_array[ledCount];
  for(int i = ledCount; i > 0; i--){
    bit_array[i-1] = number & 1; 
    number >>= 1;
  }
  for(int i = 0; i < ledCount; i++){
      if(bit_array[i] == 1){
        digitalWrite(leds[i], ON);
        
        }
      else{
        digitalWrite(leds[i], OFF);
        }  
    }
}

void counter(){
    unsigned long time_now = millis();
    for(int i = 0; i < buttonCount; i++){
        bool pressed = !digitalRead(buttons[i]);
        if(pressed && buttons[i] == button1_pin && pressed != prevpres[i]){
            count++;           
            prevpres[i] = pressed;
            timer = time_now;
          } 
        
        if(pressed && buttons[i] == button2_pin && pressed != prevpres[i]){
              count--;
              prevpres[i] = pressed;
              timer2 = time_now;
            
           
        } 
        if(!pressed&& prevpres[i]){
            prevpres[i] = !prevpres[i];
            activated[i] = false;
        }
        
        if(pressed && buttons[i] == button1_pin && pressed == prevpres[i]){
           if((!activated[0]) && time_now - timer >= wait_off){
              activated[0] = !activated[0];
              count++;
              timer += wait_off;            
           }   
           else if(activated[0] && time_now - timer >= wait_on){
                count++;              
                timer += wait_on;
                }           
          }
        if(pressed && buttons[i] == button2_pin && pressed == prevpres[i]){
          if((!activated[1]) && time_now - timer2 >= wait_off){
            activated[1] = !activated[1];
            count--;            
            timer2 += wait_off;
            }            
          else if(activated[1] && time_now - timer2 >= wait_on){
            count--;
            timer2 += wait_on;
            }
          }                      
    }
  }



void setup() 
  {
  // put your setup code here, to run once:
  for (auto led : leds) {
    pinMode(led, OUTPUT);
    digitalWrite(led, OFF);  
  }
  for (auto button : buttons)
    {
      pinMode(button, INPUT);
    }  
  }


void loop() {
  counter();
  turn_on_off(count);
}
