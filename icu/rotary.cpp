#include "rotary.h"
#define CLICK_THRESHOLD 100
int counter = 0;

string currentDir ="";
unsigned long lastButtonPress = 0;

void displayRotary(int currentStateCLK, int currentStateSW, int currentStateDT, int& lastStateCLK, int& displayScreen, int& rowCount, int &torque)
{
 if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
{
  // Serial.println(1);

  // If the DT state is different than the CLK state then
  // the encoder is rotating CCW so decrement
  
  if (currentStateDT == currentStateCLK)
  {
    torque = torque - 10;
  }
  else
  {
    // Encoder is rotating CW so increment
    torque = torque + 10;
  }
}
  // Save the current state of the CLK pin for the next iteration
  lastStateCLK = currentStateCLK;
  
if (currentStateSW == LOW) // LOW is 0V, testing if redefining works
{
  //  Serial.println(1);
  // if 50ms have passed since last LOW pulse, it means that the
  // button has been pressed, released and pressed again
  if (millis() - lastButtonPress > 5)
  {
    counter++;
    displayScreen = counter % NUMBER_OF_SCREENS;
    Serial.println("Button pressed!");
  }
  /* if (displayScreen == MENU_SCREEN)
  {
    displayScreen = rowCount;
  }

  else 
  {
    displayScreen = MENU_SCREEN;
//    Serial.println("FUCK IS THIS NOT WORKING?!?!?!?!");
  }
  */
  // Remember last button press event
  lastButtonPress = millis();
}

delay(1);
}

