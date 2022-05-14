#include "funshield.h"
#include "input.h"
#include <cstring>

SerialInputHandler input;

// map of letter glyphs
constexpr byte LETTER_GLYPH[] {
  0b10001000,   // A
  0b10000011,   // b
  0b11000110,   // C
  0b10100001,   // d
  0b10000110,   // E
  0b10001110,   // F
  0b10000010,   // G
  0b10001001,   // H
  0b11111001,   // I
  0b11100001,   // J
  0b10000101,   // K
  0b11000111,   // L
  0b11001000,   // M
  0b10101011,   // n
  0b10100011,   // o
  0b10001100,   // P
  0b10011000,   // q
  0b10101111,   // r
  0b10010010,   // S
  0b10000111,   // t
  0b11000001,   // U
  0b11100011,   // v
  0b10000001,   // W
  0b10110110,   // ksi
  0b10010001,   // Y
  0b10100100,   // Z
};
constexpr byte EMPTY_GLYPH = 0b11111111;

constexpr int positionsCount = 4;
constexpr unsigned int scrollingInterval = 300;

int pos = 0;
char arr[positionsCount] = {' ',' ',' ',' '};

const char *str;
int len_str;

int letter_pos = 0;
unsigned long last_time = 0;

bool end_of_str = false;

void displayChar(char ch, byte pos)
{
  byte glyph = EMPTY_GLYPH;
  if (isAlpha(ch)) {
    glyph = LETTER_GLYPH[ ch - (isUpperCase(ch) ? 'A' : 'a') ];
  }
  
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST, glyph);
  shiftOut(data_pin, clock_pin, MSBFIRST, 1 << pos);
  digitalWrite(latch_pin, HIGH);
}

void get_letter(){
  if(letter_pos >= len_str){
    end_of_str = !end_of_str;
    letter_pos = 0;
    str = input.getMessage();
    len_str = strlen(str);
    if(end_of_str){
      len_str = positionsCount;
      str = "    ";
    }
  }
  arr[positionsCount-1] = str[letter_pos++];
}


void multiplex(char letter){
  displayChar(letter, pos);
  ++pos %= positionsCount;
  }


void change_letters(){
  for(int i = 0; i < positionsCount-1; i++){
      arr[i] = arr[i+1];
      
  }
  get_letter();
}


void setup() {
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  input.initialize();
  str = input.getMessage();
  len_str = strlen(str);
}



void loop() {
  unsigned long time_now = millis();
  input.updateInLoop();
  multiplex(arr[pos]);
  if(time_now - last_time >= scrollingInterval){
    last_time += scrollingInterval; 
    change_letters();
  }

}
