#include <Servo.h>
/* 
ledLiv  = 2;
ledCoc  = A0;
ledCom  = 4;
ledGar  = 5;
ledBano = 6;
ledEnt  = 7;
ledDor1 = 8;
ledDor2 = 9;
ledPas  = 12;
ledOfi  = 13; 
*/
const uint8_t leds[10] = {2, A0, 4, 5, 6, 7, 8, 9, 12, 13};
int Sfunc1 =0;
int Sfunc2 =0;
int Sfunc3 =0;
Servo Scom;
Servo Sdorm;
Servo Spudorm;
void setup() {
  Serial.begin(115200);
  Scom.attach(10);
  Sdorm.attach(11);
  Spudorm.attach(3);
  Sdorm.write(35);
  Scom.write(140);
  for(int i=0; i<10; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  if (Serial.available()) {
    int selec = Serial.parseInt();
    switch(selec){
      case 10:
        if(Sfunc1 == 1){
          Scom.write(140);
          Sfunc1=0;
        }else{
          Scom.write(0);
          Sfunc1=1;
        }
      break;
      case 11:
        if(Sfunc2 == 1){
          Sdorm.write(35);
          Sfunc2=0;
        }else{
          Sdorm.write(140);
          Sfunc2=1;
        }
      break;
      case 12:
        if(Sfunc3 == 1){
          Spudorm.write(120);
          Sfunc3=0;
        }else{
          Spudorm.write(0);
          Sfunc3=1;
        }
      break;
      default:
        digitalWrite(leds[selec], !digitalRead(leds[selec]));
      break;
    }
  }
}
