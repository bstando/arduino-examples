#include "MIDIUSB.h"
#include <CapacitiveSensor.h>
#define NUM_OF_SAMPLES  20   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   400  // Capactive reading that triggers a note (adjust to fit your needs)
#define C1(Y) CapacitiveSensor(0, Y)
#define C2(Y) CapacitiveSensor(2, Y)
#define C3(Y) CapacitiveSensor(4, Y)
#define C4(Y) CapacitiveSensor(6, Y)
#define C5(Y) CapacitiveSensor(8, Y)
#define C6(Y) CapacitiveSensor(10, Y)
CapacitiveSensor inputs[] = {C1(1),C2(3),C3(5),C4(7),C5(9),C6(11)};
int notes[] = {60,61,62,63,64,65};
bool presseds[] = {false,false,false,false,false,false};


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
   for(int i=0;i<10;i++)
   inputs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
   //Serial.begin(9600);
   
}
void loop() {
  for(int i=0;i<6;i++)
  if(inputs[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD)
  {
    if(!presseds[i]){
    noteOn(0, notes[i], 64);   // Channel 0, selected note, normal velocity
    MidiUSB.flush();
    presseds[i]=true;
    //Serial.print("Press: ");
    //Serial.println(notes[i]);
    }
    
  }
  else
  {
    if(presseds[i])
    {
      noteOff(0, notes[i], 64);  // Channel 0, selected note, normal velocity
      MidiUSB.flush();
      presseds[i]=false;  
      //Serial.print("Release: ");
      //Serial.println(notes[i]);
    }
    
  }
  
  
}
