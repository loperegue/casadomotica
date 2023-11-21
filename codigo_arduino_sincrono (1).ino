/* 
ledLiv  = 2;
ledCoc  = 3;
ledCom  = 4;
ledGar  = 5;
ledBano = 6;
ledEnt  = 7;
ledDor1 = 8;
ledDor2 = 9;
ledPas  = 10;
ledOfi  = 11; 
*/
const uint8_t leds[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
  Serial.begin(115200);
  for (int i=0; i<10; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  if (Serial.available()) {
    Serial.println(leds[0]);
    int selec = Serial.parseInt();
    digitalWrite(leds[selec], !digitalRead(leds[selec]));
  }
}