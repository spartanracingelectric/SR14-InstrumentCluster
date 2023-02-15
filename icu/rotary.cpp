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

/**
 * @brief redefines counter of rotary depending on the digitalRead from icu.ino
 * 
 */
void rotary__update_state()
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

/**
 * @brief Updates LCD screen based on rotary counter that's updated from rotary__update_State()
 * 
 */
void rotary__update_LCD()
{
          switch(counter % NUMBER_SCREEN) {// NUMBER_SCREEN is number of screens to limit counter to a rnge between 0 - #ofscreens
          case 1:
          // rotate rotary to change row highlighted
          // button press to change to that screen
                    break;
          case 2:
          // Testing screen button press to change to menu screen
                    break;
          case 3:
          // debug vcu rotate rotary to sweep through screens
          // press rotary to exit screen
                    break;
          case 4:
          // debug bms screen rotate rotary to sweep through screens
          // press rotary to exit screen
                    break;
          default:
          // button press change to menu screen
                    break;
          }
}
