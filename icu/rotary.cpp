#include "rotary.h"

int counter = 0;

string currentDir ="";
unsigned long lastButtonPress = 0;

void displayRotary(int currentStateCLK, int currentStateSW, int currentStateDT, int& lastStateCLK, int& displayScreen, int& rowCount)
{
  
// If last and current state of CLK are different, then pulse occurred
// React to only 1 state change to avoid double count
// currentStateCLK = digitalRead(CLK);
//  Serial.println(currentStateCLK);
//            Serial.println(lastStateCLK);
// Serial.println(currentStateSW);
// Serial.println(currentStateDT);

if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
{
  // Serial.println(1);

  // If the DT state is different than the CLK state then
  // the encoder is rotating CCW so decrement
  if (currentStateDT == currentStateCLK)
  {
    counter--;
    if (displayScreen != MENU_SCREEN)
    {
//      displayScreen = counter % NUMBER_OF_SCREENS;
    }
    else if (displayScreen == MENU_SCREEN)
    {
      rowCount = abs((rowCount - 1) % NUMBER_OF_ROWS);
    }
      currentDir = "CCW";
  }
  else
  {
    // Encoder is rotating CW so increment
    counter++;
    if (displayScreen != MENU_SCREEN)
    {
//      displayScreen = counter % NUMBER_OF_SCREENS;
    }
    else if (displayScreen == MENU_SCREEN)
    {
      rowCount =  (rowCount + 1) % NUMBER_OF_ROWS;
    }
    currentDir = "CW";
  }
  char ch[5]; 
  strcpy(ch, currentDir.c_str()); //convert to Cstring to print out

  Serial.print("Direction: ");
  Serial.print(ch);
  Serial.print(" | Counter: ");
  Serial.println(counter);
}

// Remember last CLK State
lastStateCLK = currentStateCLK;

// If we detect LOW signal, button is pressed
//  currentStateSW = digitalRead(SW);
if (currentStateSW == LOW) // LOW is 0V, testing if redefining works
{
  //  Serial.println(1);
  // if 50ms have passed since last LOW pulse, it means that the
  // button has been pressed, released and pressed again
  if (millis() - lastButtonPress > 50)
  {
  Serial.println("Button pressed!");
  }
  if (displayScreen == MENU_SCREEN)
  {
    displayScreen = rowCount;
  }
  else 
  {
    displayScreen = MENU_SCREEN;
//    Serial.println("FUCK IS THIS NOT WORKING?!?!?!?!");
  }
  // Remember last button press event
  lastButtonPress = millis();
}

delay(1);
}
