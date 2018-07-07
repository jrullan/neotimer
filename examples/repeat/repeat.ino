#include <neotimer.h>

Neotimer mytimer = Neotimer(1000); // Set timer's preset to 1s

int count = 0;
const int BTN1 = 5;
const int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(BTN1,INPUT);
  pinMode(LED,OUTPUT);
}

void loop(){
  
  if(mytimer.repeat(10)){
    
    digitalWrite(LED,!digitalRead(LED)); // Let's blink each second

    Serial.print("Calling this ");
    Serial.print(++count);
    Serial.print(" times: LED is ");    
    if(digitalRead(LED)){ 
      Serial.println("ON");
    }else{
      Serial.println("OFF");
    }

  }

  if(digitalRead(BTN1) == HIGH){   
    mytimer.repeatReset(); // If a button is pressed reset the repeat counter
    count=0;
  }

}
