/*  Example of playing a sampled sound,
    using Mozzi sonification library.
  
    Demonstrates one-shot samples scheduled
    with EventDelay.
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.0/3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
*/

//#include <ADC.h>  // Teensy 3.0/3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Sample.h> // Sample template
#include <samples/cronch.h>
#include <EventDelay.h>
const int buttonPin = 4;
int buttonState = LOW;
#define CONTROL_RATE 64

// use: Sample <table_size, update_rate> SampleName (wavetable)
Sample <cronch_NUM_CELLS, AUDIO_RATE> aSample(cronch_DATA);

// for scheduling sample start
EventDelay kTriggerDelay;

void setup(){

  startMozzi(CONTROL_RATE);
  aSample.setFreq((float) (cronch_SAMPLERATE * 2) / (float) cronch_NUM_CELLS); // play at the speed it was recorded
  kTriggerDelay.set(1500); // 1500 msec countdown, within resolution of CONTROL_RATE
}


void updateControl(){
 static char prevButton; // static causes it to keep the state from the last call...

  pinMode(buttonPin, INPUT); // this should be in setup(), but whatever :)
  buttonState = digitalRead(buttonPin);
  if(kTriggerDelay.ready() &&( buttonState == HIGH) &&( prevButton == LOW)){
    aSample.start();
    kTriggerDelay.start();    
  }
 prevButton = buttonState; // update our history variable.

}


int updateAudio(){
  return (int) aSample.next();
}


void loop(){
  audioHook();
}


