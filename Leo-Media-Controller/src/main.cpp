#include <Arduino.h>
#include <HID-Project.h>
#include <RotaryEncoder.h>

#define KEYDELAY 5 //Debounce 5ms
#define PIN_PUSH 3
#define PIN_IN1 10
#define PIN_IN2 11

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int Get_Encoder_Direction();
void Switch_Play_Device();
void Volume_Up();
void Volume_Down();
bool Encoder_Button_Read();

static int pos = 0;

void setup() {
  // put your setup code here, to run once
  pinMode(PIN_PUSH,INPUT_PULLUP);
  Consumer.begin();
  BootKeyboard.begin();
  BootKeyboard.releaseAll();
  Serial.begin(9600);
}

void loop() {

  int direction = Get_Encoder_Direction();

  if(direction==1){
    Volume_Up();
  }
  else if(direction==-1){
    Volume_Down();
  }

  if(Encoder_Button_Read()){
    Switch_Play_Device();
    Serial.println("HH");
  }
}



int Get_Encoder_Direction(){
  encoder.tick();
  int newPos = encoder.getPosition();

  //One call per tick
  /*
  if ((pos-newPos)>1 || (pos-newPos)<-1) {
    int direction = (int)(encoder.getDirection());
    pos = newPos;
    return direction;
  }
  */

  //Two call per tick
  
  if (pos != newPos) {
    int direction = (int)(encoder.getDirection());
    pos = newPos;
    return direction;
  }
  
  return 0;
}


void Volume_Up(){
  Consumer.write(MEDIA_VOL_UP);
}


void Volume_Down(){
  Consumer.write(MEDIA_VOL_DOWN);
}


void Switch_Play_Device(){
    //Shortcut key for switch play device of Sound Switch Stable is CTRL+ALT+F11
    BootKeyboard.press(HID_KEYBOARD_LEFT_CONTROL);
    BootKeyboard.press(HID_KEYBOARD_LEFT_ALT);
    BootKeyboard.press(HID_KEYBOARD_F11);
    BootKeyboard.releaseAll();
    delay(1000);
}


bool Encoder_Button_Read(){
  return !digitalRead(PIN_PUSH);
}