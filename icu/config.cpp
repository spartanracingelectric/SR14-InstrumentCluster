#include "config.h"

// Rotary

int counterRotary = 0;
int currentStateCLK = 0;
int currentStateDT = 0;
int lastStateCLK = 0;
int currentStateSW = 0;
int counterSW = 0; // Switches counter, x % 2 = 1 complete press
int counterDelaySW = 0;
unsigned long lastButtonPress = 0;
// strcpy(currentDirection, "   "); // just an example of reassigning c-string

// Display Screen Status
// 0 for Testing
// 1 for Minimalist
// 2 for Menu
// 3 for BMS Display
// 4 for VCU Display
int displayScreen = 0;
int rowCount = 0; // for button selection

// LCD
float hv = 0.0f;
float hvCurr = 0.0f;
float soc = 0.0f;
float lv = 0.0f;
float hvtemp = 0.0f;
float hvlow = 0.0f;
uint32_t curr_millis = 0;
