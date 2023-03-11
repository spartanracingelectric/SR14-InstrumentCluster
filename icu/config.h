#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
// #include <string>
using namespace std;

/********************************************************************/
/*  INSTRUMENT CLUSTER - SETUP CONFIGURATION FILE (for ports, etc)  */
/*                                                                  */
/********************************************************************/

/*---------------------------------------------------------------------------/
/ GLOBAL VARIABLES
/---------------------------------------------------------------------------*/

// Rotary
extern int counterRotary;
extern char currentDirection[4]; // "_ _ _ null" for a c-string
extern int currentStateCLK;
extern int currentStateDT;
extern int lastStateCLK;
extern int currentStateSW;
extern int counterSW; // Switches counter
// extern int counterDelaySW; // delayed counter for switch to monitor when a change happens for rotary.cpp
extern unsigned long lastButtonPress;

// LCD
extern float hv;
extern float hvCurr;
extern float soc;
extern float lv;
extern float hvtemp;
extern float hvlow;
extern uint32_t curr_millis;

// Display Screen Status
// 0 for Testing
// 1 for Minimalist
// 2 for Menu
// 3 for BMS Display
// 4 for VCU Display
extern int displayScreen;
extern int rowCount;        // for button selection
#define NUMBER_OF_SCREENS 5 // change when add or subtract screens
#define TESTING_SCREEN 0
#define MINIMALIST_SCREEN 1
#define MENU_SCREEN 2
#define DEBUG_BMS_SCREEN 3
#define DEBUG_VCU_SCREEN 4

/*---------------------------------------------------------------------------/
/ BOARD REVISION AND CAR ENGINE TYPE
/---------------------------------------------------------------------------*/

// 'A' for Rev A
// 'B' for Rev B
// #define BOARD_REVISION 'A'
#define BOARD_REVISION 'B'

// #define POWERTRAIN_TYPE 'C'
#define POWERTRAIN_TYPE 'E'

// Set to 1 if you want to print the input data over serial
#define SERIAL_DEBUG_EN 0

/*---------------------------------------------------------------------------/
/ DRIVER PARAMETERS
/---------------------------------------------------------------------------*/

#define HVLOW_THRESHOLD_FLASH_MS 750
#define HVTEMP_THRESHOLD_FLASH_MS 750

#define LCD_UPDATE_MS 500

/*---------------------------------------------------------------------------/
/ PIN INITIALIZATIONS
/---------------------------------------------------------------------------*/

//  Rev A
#if (BOARD_REVISION == 'A')
//  LCD
#define PICO_LCD_SPI_CS 2
#define PICO_LCD_SPI_MOSI 4
#define PICO_LCD_SPI_SCK 5
#define PICO_LCD_A0 3
#define PICO_LCD_RST U8X8_PIN_NONE
//  LEDS, MAX7219
#define PICO_LED_SPI_SCK 18
#define PICO_LED_SPI_MOSI 19
#define PICO_LED_SPI_CS 13
// CAN, MCP2515
#define PICO_CAN_SPI_SCK 18
#define PICO_CAN_SPI_MOSI 19
#define PICO_CAN_SPI_MISO 16
#define PICO_CAN_SPI_CS 17

//  Rev B
#elif (BOARD_REVISION == 'B')
//  LCD
#define PICO_LCD_SPI_CS 5
#define PICO_LCD_SPI_MOSI 3
#define PICO_LCD_SPI_SCK 2
#define PICO_LCD_A0 4
#define PICO_LCD_RST 1
//  LEDS, MAX7219
#define PICO_LED_SPI_SCK 18
#define PICO_LED_SPI_MOSI 19
#define PICO_LED_SPI_CS 17
// CAN, MCP2515
#define PICO_CAN_SPI_SCK 10
#define PICO_CAN_SPI_MOSI 11
#define PICO_CAN_SPI_MISO 12
#define PICO_CAN_SPI_CS 13
#define PICO_CAN_INT 14
#define PICO_CAN_RST 15
#endif

/*---------------------------------------------------------------------------/
/ ROTARY AND BUTTON PINS
/---------------------------------------------------------------------------*/
#define BUT1 9  // PINC0
#define BUT2 10 // PINC1
#define BUT3 11 // PINC2
#define BUT4 12 // PINC3

// Rotary Encoder Inputs
#define CLK 9
#define DT 10
#define SW 11

#define DEBOUNCE_TIME 600
#define LOCK_TIME 100

#define HOLD_TIME 1000 // Button hold time for bottom buttons on default screen

/*---------------------------------------------------------------------------/
/ CAN BUS ADDRESSES
/---------------------------------------------------------------------------*/
/* CAN packet addresses based on the DBC file */

// #if (POWERTRAIN_TYPE == 'C')
// //#define CANBUS_SPEED 1000UL * 1000UL //1 Mbit/s
// #define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
// #define CAN_RPM_ADDR    0x640
// #define CAN_GEAR_ADDR   0x703
// // lv, drs, oil pressure, coolant temp

// #if (POWERTRAIN_TYPE == 'E')
#define CANBUS_SPEED 500UL * 1000UL // 500 kbit/s
#define CAN_RPM_ADDR 0x0A5
#define CAN_LV_ADDR 0x507
#define CAN_HV_ADDR 0x620
#define CAN_BMS_FAULT_ADDR 0x602 // dec: 1538
#define CAN_BMS_WARN_ADDR 0x604  // dec: 1540
#define CAN_BMS_STAT_ADDR 0x610  // dec: 1552 // system status (should be idle - 1)

#define CAN_HV_CURRENT_ADDR 0x620
#define CAN_HV_ADDR 0x620 // dec: 1568
#define CAN_SOC_ADDR 0x621
#define CAN_HVLOW_ADDR 0x622
#define CAN_BAT_TEMP_ADDR 0x623

// wrong addresses
#define CAN_REGEN_ADDR 0x508
// #endif

//  LOW VOLTAGE
/////////////////////
#define LV_WARNING_THRESHOLD 12.0f
#define LV_OFFSET .8f

//  WHEEL SPEEDS
/////////////////////
// Wheel diameter in inches
#define WHEEL_DIAMETER_IN 16.0f
#define WHEEL_CIRCUMFERENCE_M (WHEEL_DIAMETER_IN * 0.0254 * 3.141f)
#define METERS_SEC_TO_MPH 2.237f

#define MAX72XX_HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#ifndef BOARD_REVISION
#error "Select a board revision"
#endif
#ifndef POWERTRAIN_TYPE
#error "Select a powertrain type (C for Combustion or E for Electric)"
#endif

/*---------------------------------------------------------------------------/
/ HELPFUL MACROS
/---------------------------------------------------------------------------*/
#define MAX_LED_BRIGHTNESS 0xF

#endif /* CONF_H_ */
