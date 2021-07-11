// dual-axis CNC pendant
// CC BY-NC-ND 4.0 License, (c) Dr Nikolay Chekasov, June 2021
// check the video for comments and clarifications
// https://youtu.be/v_h2h0EPGog

#define pin_encoderX1 2
#define pin_encoderX2 3
#define pin_encoderZ1 6
#define pin_encoderZ2 7

#define pin_buttonX   4     //connect to one side of the button, the other - ground
#define pin_buttonZ   5

#define pin_left1     12
#define pin_left2     11
#define pin_left3     10
#define pin_right1    13
#define pin_right2    A0
#define pin_right3    A1

// https://forum.arduino.cc/t/keyboard-write-with-number-pad-keys-from-leonardo/175304
// https://www.arduino.cc/en/Reference/KeyboardModifiers
#define key_X_up      218
#define key_X_down    217
#define key_Z_up      215
#define key_Z_down    216
#define rotary_press  221

#define mod_jog       0x80  // Ctrl + J
#define mod_cycle     0x82  // Alt + J
#define jod_button    'j'
#define left1         ''
#define left2         ''
#define left3         ''
#define right1        ''
#define right2        ''
#define right3        ''

#define cycleDelay   20   // cycle delay in milliseconds

//#define DEBUG       1  
#include <MD_REncoder.h>    // https://github.com/MajicDesigns/MD_REncoder
MD_REncoder encX = MD_REncoder(pin_encoderX1, pin_encoderX2);
MD_REncoder encZ = MD_REncoder(pin_encoderZ1, pin_encoderZ2);

#include "Keyboard.h"       // standard arduino library
#include "OneButton.h"      // https://www.arduino.cc/reference/en/libraries/onebutton/
OneButton buttonX(pin_buttonX, true);
OneButton buttonZ(pin_buttonZ, true);
OneButton buttonLeft1(pin_left1, true);
OneButton buttonLeft2(pin_left2, true);
OneButton buttonLeft3(pin_left3, true);
OneButton buttonRight1(pin_right1, true);
OneButton buttonRight2(pin_right2, true);
OneButton buttonRight3(pin_right3, true);

void setup() 
{
  #ifdef DEBUG
    Serial.begin(57600);
  #endif
  encX.begin();
  encZ.begin();
  buttonX.attachClick(sendStop);
  buttonZ.attachClick(sendStop);
  buttonLeft1.attachClick(pressLeft1);
  buttonLeft2.attachClick(pressLeft2);
  buttonLeft3.attachClick(pressLeft3);
  buttonRight1.attachClick(pressRight1);
  buttonRight2.attachClick(pressRight2);
  buttonRight3.attachClick(pressRight3);
}

void loop() 
{
  buttonX.tick();
  buttonZ.tick();
  buttonLeft1.tick();
  buttonLeft2.tick();
  buttonLeft3.tick();  
  buttonRight1.tick();
  buttonRight2.tick();
  buttonRight3.tick();
  
  int8_t x = encX.read();
  int8_t z = encZ.read();
  
  
  if (x==DIR_CW ) 
  {
    #ifdef DEBUG
      Serial.print("X axis moved <: ");
      Serial.println(x);
    #else
      Keyboard.write(key_X_up); 
    #endif
  }
  if (x==DIR_CCW) 
  {
    #ifdef DEBUG
      Serial.print("X axis moved >: ");
      Serial.println(x);
    #else
      Keyboard.write(key_X_down); 
    #endif
  }
  
  if (z==DIR_CW ) 
  {
    #ifdef DEBUG
      Serial.print("Z axis moved >: ");
      Serial.println(z);
    #else
      Keyboard.write(key_Z_up); 
    #endif
  }
  
  if (z==DIR_CCW) 
  {
    #ifdef DEBUG
      Serial.print("Z axis moved <: ");
      Serial.println(z);
    #else
      Keyboard.write(key_Z_down); 
    #endif
  }

  if (x+z)
  {
    x=0;
    z=0;
    Keyboard.releaseAll();
    delay(cycleDelay);
  }
}

void sendStop() { // send stop key
  #ifdef DEBUG
    Serial.println("Stop button pressed");
  #else
    Keyboard.write(rotary_press); 
    Keyboard.releaseAll();
  #endif
}


void pressLeft1() { //pressing the button, left 1
}

void pressLeft2() { //pressing the button, left 2
}

void pressLeft3() { //pressing the button, left 3
}

void pressRight1() { //pressing the button, right 1
}

void pressRight2() { //pressing the button, right 1
}

void pressRight3() { //pressing the button, right 1
}

void setModJog() {  //send jog mode
  #ifdef DEBUG
    Serial.println("Button Mode Jog");
  #else
    Keyboard.press(mod_jog);
    delayMicroseconds(50);
    Keyboard.write(jod_button); 
    delayMicroseconds(50);
    Keyboard.releaseAll();
  #endif
} 

void setModCycle() {  //send jog mode
  #ifdef DEBUG
    Serial.println("Button Cycle Jog");
  #else
    Keyboard.press(mod_cycle);
    delayMicroseconds(50);
    Keyboard.write(jod_button); 
    delayMicroseconds(50);
    Keyboard.releaseAll();
  #endif
} 
