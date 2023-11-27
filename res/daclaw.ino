
#include "Keyboard.h"

// pins
#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 7
#define KEY_SUPER 8

#define NUM_KEYS 6 // super doesn't count as a regular key

#define KEY_DELAY 350
#define REPEAT_DELAY 20

#define key_down(k) (digitalRead((k)) == LOW)

//  3  2  1
//  4  5  6

const uint8_t KEYS[]={
  KEY_3,
  KEY_2,
  KEY_1,

  KEY_4,
  KEY_5,
  KEY_6,
};

// super off
const uint8_t KEYMAP[] = {
  KEY_F13,
  KEY_F14,
  KEY_F15,
  KEY_F16,
  KEY_F17,
  KEY_F18,
};

// super on
const uint8_t SUPER_KEYMAP[] = {
  KEY_F19,
  KEY_F20,
  KEY_F21,
  KEY_F22,
  KEY_F23,
  KEY_F24,
};

// const uint8_t KEYMAP[] = {
//   '1',
//   '2',
//   '3',
//   '4',
//   '5',
//   '6',
// };

// // super on
// const uint8_t SUPER_KEYMAP[] = {
//   'a',
//   'b',
//   'c',
//   'd',
//   'e',
//   'f',
// };

struct t_key_state{
  bool down;
  unsigned long down_time;
  unsigned long repeat;
  int stabilization_delay;
};

struct t_key_state key[NUM_KEYS];

void setup() {
  for (int i=0; i< NUM_KEYS; i++){
    pinMode(KEYS[i], INPUT);
    digitalWrite(KEYS[i], HIGH);
    key[i].down = false;
  }

  pinMode(KEY_SUPER, INPUT);
  digitalWrite(KEY_SUPER, HIGH);
  Keyboard.begin();
  Keyboard.releaseAll();
}


void send_key(int i, bool super){
  if (key[i].stabilization_delay > 0) return;
  Keyboard.write(super? SUPER_KEYMAP[i] : KEYMAP[i]);
  key[i].stabilization_delay = 100;
}

void loop() {
  for (int i=0; i< NUM_KEYS; i++){

    bool down = key_down(KEYS[i]);
    bool super = key_down(KEY_SUPER);

    if (down){
      if (!key[i].down){
        key[i].repeat = key[i].down_time = millis();
        send_key(i, super);
      } else {
        if (millis() - key[i].down_time > KEY_DELAY){
          // repeating
          if (millis() - key[i].repeat > REPEAT_DELAY){
            send_key(i, super);
            key[i].repeat = millis();
          }
        }
      }
    } 
    // update state
    key[i].down = down;
    if (key[i].stabilization_delay > 0) key[i].stabilization_delay--; 
  }
}
