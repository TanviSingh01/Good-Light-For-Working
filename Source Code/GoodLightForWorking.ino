#include <Keyboard.h>
#define LIGHT A0

// Variable declaration
int avgLightLevel;
bool isAlertDisplayed = false;

// Initial Setup
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LIGHT, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
  // while the serial stream is not open, do nothing:
  while (!Serial)
  {
    // do nothing
  } ;

  //Take 16 readings from the light sensor and average them together
  avgLightLevel = 0;
  for (int x = 0 ; x < 16 ; x++)
    avgLightLevel += analogRead(LIGHT);
  avgLightLevel /= 16;
  Serial.print("Avg: ");
  Serial.println(avgLightLevel);
}

// the loop function runs over and over again forever
void loop() {
  int lightLevel = analogRead(LIGHT);
  unsigned long previousTime = 0;
  byte seconds ;

  Serial.print("Current: ");
  Serial.println(lightLevel);

  if (lightLevel > (avgLightLevel)*3/2)
  {
    Serial.print("Inside outer if!");
 if (millis() >= (previousTime)) 
  {
    Serial.print("Inside intermediate if!");
     previousTime = previousTime + 1000;  
     if (isAlertDisplayed == false) // original value = 60 (1 minute)
     {
      // Display pop-up
      Serial.print("Display alert now!");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('h');
      Keyboard.releaseAll();
      delay(5000);
      lightLevel = analogRead(LIGHT);
      if(lightLevel > (avgLightLevel))
      {
      Serial.print("Inside Lock Loop!");
      Keyboard.press(KEY_LEFT_GUI);              //Press the left windows key.
      Keyboard.press('l');                       //Press the "l" key.
      Keyboard.releaseAll();
      isAlertDisplayed == false;
     }
     }
     

  } // end 1 second
   
   delay(1000); // delay of 1 second
   lightLevel = analogRead(LIGHT); //We need to take another reading to be able to exit the while loop
  } 

}
