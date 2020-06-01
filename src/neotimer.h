#ifndef NEOTIMER_H
#define NEOTIMER_H

#define NEOTIMER_INDEFINITE -1
#define NEOTIMER_UNLIMITED -1


#include <Arduino.h>

class Neotimer{
	public:
	//Methods
	Neotimer();
	Neotimer(unsigned long _t);      //Constructor
	~Neotimer();            //Destructor

	void init();            //Initializations
	boolean done();         //Indicates time has elapsed
	boolean repeat(int times);
	boolean repeat(int times, unsigned long _t);
	boolean repeat();
	void repeatReset();
	boolean waiting();		// Indicates timer is started but not finished
	boolean started();		// Indicates timer has started
	void start();			//Starts a timer
	unsigned long stop();	//Stops a timer and returns elapsed time
	unsigned long getEllapsed();	// Gets the ellapsed time
	void restart();
	void reset();           //Resets timer to zero
	void set(unsigned long t);
	unsigned long get();
	boolean debounce(boolean signal);
	int repetitions = NEOTIMER_UNLIMITED;

	private:

	struct myTimer{
		unsigned long time;
		unsigned long last;
		boolean done;
		boolean started;
	};

	struct myTimer _timer;
	boolean _waiting;
};

//Default constructor
Neotimer::Neotimer(){
	this->_timer.time = 1000; //Default 1 second interval if not specified
}

Neotimer::Neotimer(unsigned long _t){
  this->_timer.time = _t;
}

//Default destructor
Neotimer::~Neotimer(){

}

//Initializations
void Neotimer::init(){
  this->_waiting = false;
}

/*
 * Repeats a timer x times
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10)){
 * 	  do something 10 times, every second (default)
 * }
 */
boolean Neotimer::repeat(int times){
	if(times != NEOTIMER_UNLIMITED){
		// First repeat
		if(this->repetitions == NEOTIMER_UNLIMITED){
			this->repetitions = times;
		}
		// Stop
		if(this->repetitions == 0){
			return false;
		}

		if(this->repeat()){
			this->repetitions--;
			return true;
		}
		return false;
	}
	return this->repeat();
}

/*
 * Repeats a timer x times with a defined period
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10,5000)){
 * 	  do something 10 times, every 5 seconds
 * }
 */
boolean Neotimer::repeat(int times, unsigned long _t){
	this->_timer.time = _t;
	return this->repeat(times);
}

/*
 * Repeats a timer indefinetely
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat()){
 * 	  do something indefinetely, every second (default)
 * }
 */
boolean Neotimer::repeat(){
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

void Neotimer::repeatReset(){
	this->repetitions = -1;
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
void Neotimer::set(unsigned long t){
  this->_timer.time = t;
}

/*
 * Gets the timer preset
 */
unsigned long Neotimer::get(){
	return this->_timer.time;
}

/*
 * Returns the debounced value of signal
 * This is very useful to avoid "bouncing"
 * of electromechanical signals
 */
boolean Neotimer::debounce(boolean signal){
	if(this->done() && signal){
		this->start();
		return true;
	}
	return false;
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
	this->reset();
  this->_timer.started = true;
  this->_waiting = true;
}

/*
 * Stops a timer
 */
unsigned long Neotimer::stop(){
  this->_timer.started = false;
  this->_waiting = false;
  return this->getEllapsed();
}

/*
 * Gets ellapsed time
 */
unsigned long Neotimer::getEllapsed(){
  return millis()-this->_timer.last;
}

/*
 * Continues a stopped timer
 */
void Neotimer::restart(){
	if(!this->done()){
		this->_timer.started = true;
		this->_waiting = true;
	}
}

/*
 * Indicates if the timer is active
 * but has not yet finished.
 */
boolean Neotimer::waiting(){
  return (this->_timer.started && !this->done()) ? true : false;
}

boolean Neotimer::started(){
	return this->_timer.started;
}

#endif
