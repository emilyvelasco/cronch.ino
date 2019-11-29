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
const int buttonPin = 5;
int buttonState = LOW;
#define CONTROL_RATE 63

// use: Sample <table_size, update_rate> SampleName (wavetable)
Sample <cronch_NUM_CELLS, AUDIO_RATE> aSample(cronch_DATA);

// for scheduling sample start
EventDelay kTriggerDelay;

boolean triggered = false;

void setup(){

  startMozzi(CONTROL_RATE);
  aSample.setFreq((float) (cronch_SAMPLERATE *1.75) / (float) cronch_NUM_CELLS); // play at the speed it was recorded
  kTriggerDelay.set(1500); // 1500 msec countdown, within resolution of CONTROL_RATE
}


void updateControl(){
  pinMode(buttonPin, INPUT);
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    if(!triggered){
      aSample.start();
      //kTriggerDelay.start();
      triggered = true;
  }
}else{
  triggered = false;
}
}

int updateAudio(){
  return (int) aSample.next();
}


void loop(){
  audioHook();
}


