# neotimer
Non blocking timer class for Arduino. 

When you use a delay() function in an Arduino sketch, the processor stops everything it is doing until this delay is completed. That is called a blocking delay, because it blocks the processor until it finishes. Many times we don't want this to happen. This timer provides a way to use time delays without blocking the processor, so it can do other things while the timer ends up. This is called a non-blocking delay timer.

The timer provides basic functionality to implement different ways of timing in a sketch. There are two main ways to use the timer, first as a Start-Stop-Reset timer.

### Start-Stop-Reset Mode
When you create an instance of the timer you must specify the preset value of the timer. Then you call start() whenever you want the timer to start. If you want to know if the timer has ended you check for done(). See the example below.

```c++
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
    //...execute this code while the timer reaches done()
  }
}
```
You can use the waiting() function to check if the timer has been started but it's not done. 
The stop() command is used to stop the timer momentarily and it returns the elapsed time since the start() was given. 
In the start-stop mode reset() initializes the timer to start from the beginning. 

In this mode the timer will keep on counting past the done() event until you call the stop() and reset(). This allows the flexibility to use it to count the time required for some external condition to become true. For example,

```c++
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
```

### Repeat mode
A convenient way to use the timer is to use the `repeat()` mode. This mode let's you repeat some code periodically X amount of times. The interval is set with the timer's `set(long t)` method. Once repeat has been called X times, it will not return true again, unless `repeatReset()` is called. The typical usage is inside an `if()` clause.

If no argument is given to repeat, it will repeat the code unlimited amount of times.

Remember, it is non-blocking so the program will skip the code when the timer is not done.
There are three variants for your convenience:

#### Variant 1
```c++ 
repeat()
``` 
In this mode it will repeat indefinitely times. The timer's preset is set using `set(long t)`.

```c++
void setup(){
  mytimer.set(2000); // Sets the timer preset to 2 second intervals
}

void loop(){
  if(mytimer.repeat()){
    Serial.println("Calling this indefinitely every 2 seconds!");
    digitalWrite(D13,!digitalRead(D13)); // Let's blink each two seconds
  }
}
```

#### Variant 2
```c++ 
repeat(int times)
``` 
In this mode you specify the times that it should repeat a task. The delay is specified by setting the timer's preset with `set(long t)`.

```c++
void setup(){
  mytimer.set(2000); // Sets the timer preset to 2 second intervals
}

void loop(){
  if(mytimer.repeat(10)){
    Serial.println("Calling this 10 times in 2 seconds intervals");
    digitalWrite(D13,!digitalRead(D13)); // Let's blink each two seconds
  }
}
```

#### Variant 3
```c++ 
repeat(int times, long t)
``` 
In this mode you specify the times that it should repeat a task and the delay at the same time. **No need to set the timer's preset using `set(long t)`**.

```c++
void loop(){
  if(mytimer.repeat(10,2000)){
    Serial.println("Calling this 10 times in 2 seconds intervals");
    digitalWrite(D13,!digitalRead(D13)); // Let's blink each two seconds
  }
}
```

#### Using `repeatReset()`
If you are using the repeat mode, after it repeats the call the amount of times set, the timer will stop repeating. If you want to restart it you can call `repeatReset()` to reset the timer's counter and start counting again. In the example below, when the repeat has been called 10 times it will stop until the user presses the button wired to D5. Once pressed the timer's counter is reset and it starts again for 10 times.

```c++
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
```
