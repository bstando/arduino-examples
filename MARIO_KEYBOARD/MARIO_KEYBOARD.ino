
#include <Keyboard.h>
#include <CapacitiveSensor.h>
#define NUM_OF_SAMPLES  20   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   400  // Capactive reading that triggers a note (adjust to fit your needs)
#define CUD(Y) CapacitiveSensor(2, Y)          
#define CLR(Y) CapacitiveSensor(5,Y)
#define CJ(Y)  CapacitiveSensor(8,Y)
#define CR(Y)  CapacitiveSensor(11,Y)
CapacitiveSensor inputs[] = {CUD(3),CUD(4),CLR(6),CLR(7),CJ(9),CR(12)};
char keys[] = {'w','s','a','d',' ',KEY_LEFT_SHIFT};
bool presseds[] = {false,false,false,false,false,false};
int i=0;
int num =0;
void setup() {
   for(int i=0;i<6;i++)
   inputs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
   Keyboard.begin();
   //Serial.begin(9600);
}
void loop() {
  for(i=0;i<6;i++)
  {
  if(inputs[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD)
  {
    if(!presseds[i]){
    Keyboard.press(keys[i]);
    presseds[i]=true;
    num++;
    //Serial.print("Pressed: ");
    //Serial.print(keys[i]);
    //Serial.println(".");
    }
   
  }
  else if(inputs[i].capacitiveSensor(NUM_OF_SAMPLES) < 200)
  {
    if(presseds[i])
    {
      
      Keyboard.release(keys[i]);
      presseds[i]=false;
      //Serial.print("Released: ");
      //Serial.print(keys[i]);
      //Serial.println(".");
    }
  }
  }
}
