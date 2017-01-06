#include <neotimer.h>

Neotimer mytimer = Neotimer(1000);
#define BTN1 4

void setup() {
  Serial.begin(9600);
  pinMode(BTN1,INPUT);
}

void loop(){
  if(digitalRead(BTN1)==HIGH){
    mytimer.start();
  }

  if(digitalRead(BTN1)==LOW){
    Serial.print("BTN1 pressed for ");
    Serial.print(mytimer.stop());
    Serial.println(" milliseconds.");
    mytimer.reset();
  }
}
