#ifndef NEOTIMER_H
#define NEOTIMER_H

#include <Arduino.h>

class Neotimer{
  public:
    //Methods
    Neotimer(long _t);      //Constructor
    ~Neotimer();            //Destructor
    void init();            //Initializations
    boolean done();         //Indicates time has elapsed
    boolean wait(long _t);  //Indicates time has elapsed
    void reset();           //Resets timer to zero
    void set(long t);
    void start();
    void stop();
    boolean waiting();
    
  private:

    typedef struct myTimer{
      long time;
      long last;
      boolean done;
      boolean started;
    };

    struct myTimer _timer;
    boolean _waiting;
};

//Default constructor
Neotimer::Neotimer(long _t){
  this->_timer.time = _t;
}

//Default destructor
Neotimer::~Neotimer(){
  
}

//Initializations
void Neotimer::init(){
  this->_waiting = false;
}


// Timer utilities functions

/*
 * Repeats a timer continuosly
 * Useful to execute a task periodically.
 * Usage: 
 * if(timer.repeat(1000)){
 * 	  do something every second
 * }
 */
boolean Neotimer::repeat(long _t){
  this->_timer.time = _t;  
  if(this->done()){
    this->reset();
    return true;
  }  
  if(!this->_timer.started){
	this->_timer.last = millis();
	this->_timer.started = true;
    this->_waiting = true;
  }
  return false;
}

/*
 * Checks if timer has finished
 * Returns true if it finished
 */
boolean Neotimer::done(){
  if(!this->_timer.started) return false;
  if( (millis()-this->_timer.last) >= this->_timer.time){
    this->_timer.done = true;
    this->_waiting = false;
    return true;
  }
  return false;
}

/*
 * Sets a timer preset
 */
void Neotimer::set(long t){
  this->_timer.time = t;
}

/*
 * Resets a timer
 */
void Neotimer::reset(){
  this->stop();
  this->_timer.last = millis();
  this->_timer.done = false;
}

/*
 * Start a timer
 */
void Neotimer::start(){
  this->_timer.started = true;
  this->_waiting = true;
}

/*
 * Stops a timer
 */
void Neotimer::stop(){
  this->_timer.started = false;
  this->_waiting = false;
}

/*
 * Indicates if the timer is active
 * but has not yet finished.
 */
boolean Neotimer::waiting(){
  return this->_waiting;
}

#endif
