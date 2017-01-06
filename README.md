# neotimer
Non blocking timer class for Arduino. Developed originally for use in the Udoo Neo as an experiment. 

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
You can stop the timer at any time and restart it using stop() and then start(). If you want to start the timer from the beginning again you can use reset(). You can also use the waiting() function to check if the timer is still waiting and it's not done.

### Repeat mode
A convenient way to use the timer is to use the repeat(delay) mode. In this mode you specify the delay in the repeat() call and it will return true when done, and false if it isn't done. It automatically resets so it is a good way to repeat some task periodically. Remember, it is non-blocking so the program will skip the code when the timer is not done.

```c++
void loop(){
  if(mytimer.repeat(2000)){
    Serial.println("Calling this periodically each two seconds");
    digitalWrite(D13,!digitalRead(D13)); // Let's blink each two seconds
  }
}
```
