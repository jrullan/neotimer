#include <neotimer.h>

Neotimer mytimer = Neotimer(1000);

void setup() {
  Serial.begin(9600);
  pinMode(D13,OUTPUT);
}

void loop(){
  if(mytimer.repeat(2000)){
    Serial.println("Calling this periodically each two seconds");
    digitalWrite(D13,!digitalRead(D13)); // Let's blink each two seconds
  }
}
