#include "rotary.h"


// void loop()
// {
//           // If last and current state of CLK are different, then pulse occurred
//           // React to only 1 state change to avoid double count
//           if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
//           {

//                     // If the DT state is different than the CLK state then
//                     // the encoder is rotating CCW so decrement
//                     if (digitalRead(DT) != currentStateCLK)
//                     {
//                               counter--;
//                               currentDir = "CCW";
//                     }
//                     else
//                     {
//                               // Encoder is rotating CW so increment
//                               counter++;
//                               currentDir = "CW";
//                     }

//                     Serial.print("Direction: ");
//                     Serial.print(currentDir);
//                     Serial.print(" | Counter: ");
//                     Serial.println(counter);
//           }

//           // Remember last CLK state
//           lastStateCLK = currentStateCLK;
// }

void displayRotary()
{
          // If last and current state of CLK are different, then pulse occurred
          // React to only 1 state change to avoid double count
          if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
          {

                    // If the DT state is different than the CLK state then
                    // the encoder is rotating CCW so decrement
                    if (currentStateDT != currentStateCLK)
                    {
                              counter--;
                              strcpy(currentDir, "CCW"); // character array requires ecxternal function for reassigning
                    }
                    else
                    {
                              // Encoder is rotating CW so increment
                              counter++;
                              strcpy(currentDir, "CW");
                    }
          }

          // // If we detect LOW signal, button is pressed
          // if (currentStateSW == 0) // LOW is 0V, testing if redefining works
          // {
          //           // if 50ms have passed since last LOW pulse, it means that the
          //           // button has been pressed, released and pressed again
          //           if (millis() - lastButtonPress > 50)
          //           {
          //                     Serial.println("Button pressed!");
          //           }

          //           // Remember last button press event
          //           lastButtonPress = millis();
          // }
}
