#include <neotimer.h>

Neotimer mytimer = Neotimer(1000); // 1 second timer

void setup(){
  Serial.begin(9600);
  mytimer.start();
}

void loop(){
  if(mytimer.done()){
    Serial.println("Timer finished");
  }

  if(mytimer.waiting()){
    
  }
}
