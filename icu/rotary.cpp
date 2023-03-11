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
 * @brief
 * redefines counter of rotary depending on the digitalRead from icu.ino
 * Returns state 1 if Clockwise or 0 if Counter-Clockwise
 *
 */
bool rotary__update_state()
{
          // If last and current state of CLK are different, then pulse occurred
          // React to only 1 state change to avoid double count
          if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
          {

                    // If the DT state is different than the CLK state then
                    // the encoder is rotating CCW so decrement
                    if (currentStateDT != currentStateCLK)
                    {
                              counterRotary--;
                              strcpy(currentDirection, "CCW"); // character array requires ecxternal function for reassigning
                              return 0;
                    }
                    else
                    {
                              // Encoder is rotating CW so increment
                              counterRotary++;
                              strcpy(currentDirection, "CW");
                              return 1;
                    }
          }

          return 1;

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
          if (currentStateSW == 0)
          {
                    counterSW++;
                    // counterDelaySW == counterSW;
                    // same switch as if button isn't pressed yet. first checks the display, then depending on the display,  checks what number row number it is in and then translates row to screen.
                    // Enter Switch Cases when button gets pressed
                    switch (displayScreen)
                    {
                    case 0: // Default Display
                              // Go to Menu
                              displayScreen = 1;
                              break;
                    case 1: // Menu
                              // Rotation -> Row 1,2,3,4,5
                              // Use Mod to loop through the pages
                              switch (rowCount)
                              {
                              case 0:
                                        displayScreen = 0;
                                        break;
                              case 1:
                                        displayScreen = 2; // Menu is Screen 1
                                        break;
                              case 2:
                                        displayScreen = 3;
                                        break;
                              case 3:
                                        displayScreen = 4;
                                        break;
                              case 4:
                                        displayScreen = 5;
                                        break;
                              }
                              break;
                    case 2: // Minimalist Display
                              // Go to Menu
                              displayScreen = 1;
                              break;
                    case 3: // BMS Display
                              // Rotation -> Page 1,2,3...
                              // Use Mod to loop through the pages
                              // Button Press -> Menu
                              displayScreen = 1;
                              break;
                    case 4: // VCU Display
                              // Rotation -> Page 1,2,3...
                              // Use Mod to loop through the pages
                              // Button Press -> Menu
                              displayScreen = 1;
                              break;
                    case 5: // Settings Display
                              // (if theres enough time)
                              // Rotation -> Rows 1,2,3,4,5
                              // Button Press -> Select that Row Option to Change
                              // Rotation -> Values 0 - End Value
                              // Button Press -> Final Value and Exit out
                              // Button Press -> Leave to Menu (Back Button)

                              // delete when adding the screen
                              break;
                    default:
                              break;
                    }
          }
          else // when button isn't pressed but there's a rotation
          {
                    switch (displayScreen)
                    {
                    case 0: // Default Screen
                              break;
                    case 1: // Menu Screen
                              rowCount = counterRotary % 5;
                              break;
                    case 2: // Minimalist Screen
                              break;
                    case 3: // BMS Screen
                              break;
                    case 4: // VCU Screen
                              break;
                    case 5: // Settings Screen
                              break;
                    default:
                              break;
                    }
          }
}
