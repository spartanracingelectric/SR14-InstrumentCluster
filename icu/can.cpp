#include "can.h"
#include "config.h"

//Skip INT pin for Rev A, set to 0
#if (BOARD_REVISION == 'A')
ACAN2515 can (PICO_CAN_SPI_CS, SPI, 15);
#elif (BOARD_REVISION == 'B')
ACAN2515 can (PICO_CAN_SPI_CS, SPI1, PICO_CAN_INT);
#endif

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL; // 16 MHz
ACAN2515Settings settings (QUARTZ_FREQUENCY, 500UL * 1000UL) ; // CAN bit rate 500s kb/s
/*
#if (POWERTRAIN_TYPE == 'C')
uint16_t curr_rpm = 0;
uint8_t curr_gear = 0;
float curr_oilpress = 0;
float curr_lv = 0;
uint8_t curr_drs = 0;


static void can__dummy_receive (const CANMessage & inMessage)
{
  uint8_t durr;
  //curr_gear = inMessage.data[1];
  //Serial.println ("Received Gear " + curr_gear) ;
}


static void can__rpm_receive (const CANMessage & inMessage)
{
  curr_rpm = ((inMessage.data[1]) | (inMessage.data[0] << 8));
  //Serial.println ("Received RPM " + curr_rpm) ;
}

static void can__gear_receive (const CANMessage & inMessage)
{
  curr_gear = inMessage.data[1];
  //Serial.println ("Received Gear " + curr_gear) ;
}

static void can__oilpress_receive (const CANMessage & inMessage)
{
//  curr_oilpress = inMessage.data[1];
}


static void can__lv_receive (const CANMessage & inMessage)
{
//  curr_lv = ((inMessage.data[0]) | (inMessage.data[1] << 8)) * 0.001f; // for e car
}

static void can__drs_receive (const CANMessage & inMessage)
{
//  curr_drs = inMessage.data[1]; // dummy line
}

// Accessors
uint16_t can__get_rpm()
{
  return curr_rpm;
}

uint8_t can__get_gear()
{
  return curr_gear;
}

float can__get_oilpress()
{
  return curr_oilpress;
}


uint8_t can__get_drs()
{
  return curr_drs;
}

float can__get_lv()
{
  return curr_lv;
}

#elif (POWERTRAIN_TYPE == 'E') // ------------------------------------------------
float curr_hv = 0;
float curr_soc = 0;
float curr_lv = 0;
float curr_hvlow = 0;
float curr_hvtemp = 0;

static void can__hv_receive (const CANMessage & inMessage)
{
  curr_hv = ((inMessage.data[4]) | (inMessage.data[5] << 8) | (inMessage.data[6] << 16) | (inMessage.data[7] << 24)) * .001f;
}

static void can__soc_receive (const CANMessage & inMessage)
{
  curr_soc = ((inMessage.data[6]) | (inMessage.data[7] << 8)) * 0.1f;
}

static void can__lv_receive (const CANMessage & inMessage)
{
  curr_lv = ((inMessage.data[0]) | (inMessage.data[1] << 8)) * 0.001f; // for e car
}

static void can__hvlow_receive (const CANMessage & inMessage)
{
  curr_hvlow = ((inMessage.data[4]) | (inMessage.data[5] << 8)) * 0.001f; // for e car
}

static void can__hvtemp_receive (const CANMessage & inMessage)
{
  curr_hvtemp = ((inMessage.data[6]) | (inMessage.data[7] << 8)) * 0.1f;
}

//Accessors
float can__get_hv()
{
  return curr_hv;
}
float can__get_soc()
{
  return curr_soc;
}

float can__get_hvtemp() // E car accumulator
{
  return curr_hvtemp;
}

float can__get_lv()
{
  return curr_lv;
}

float can__get_hvlow()
{
  return curr_hvlow;
}
#endif

const ACAN2515Mask rxm0 = standard2515Mask (0x7FF, 0, 0) ;
const ACAN2515Mask rxm1 = standard2515Mask (0x7FF, 0, 0) ;

// POWERTRAIN_TYPE == 'C'
/*
#if (POWERTRAIN_TYPE == 'C')
const ACAN2515AcceptanceFilter filters [] =
{
//  {standard2515Filter (CAN_GEAR_ADDR, 0, 0), can__drs_receive}, // not defined
//  {standard2515Filter (CAN_GEAR_ADDR, 0, 0), can__oilpress_receive}, // not defined
  {standard2515Filter (CAN_RPM_ADDR, 0, 0), can__rpm_receive}, // RXF0
  {standard2515Filter (CAN_GEAR_ADDR, 0, 0), can__gear_receive} // RXF1
  
  //{standard2515Filter (0x7FE, 0, 0), can__dummy_receive}, // RXF2
} ;
*/
// POWERTRAIN_TYPE == 'E'
#if (POWERTRAIN_TYPE == 'E')
const ACAN2515AcceptanceFilter filters [] =
{
  //Must have addresses in increasing order
  //{standard2515Filter (CAN_LV_ADDR, 0, 0), can__lv_receive},            //RXF0
  {standard2515Filter (CAN_RPM_ADDR, 0, 0), can__rpm_receive},
  {standard2515Filter (CAN_BMS_FAULT_ADDR, 0, 0), can__bms_fault_receive},  //RXF1 (new stuff)
  {standard2515Filter (CAN_BMS_WARN_ADDR, 0, 0), can__bms_warn_receive},  //RXF2
  {standard2515Filter (CAN_BMS_STAT_ADDR, 0, 0), can__bms_stat_receive},  //RXF3
  
  {standard2515Filter (CAN_HV_ADDR, 0, 0), can__hv_receive},            //RXF1
  {standard2515Filter (CAN_SOC_ADDR, 0, 0), can__soc_receive},          //RXF2
  {standard2515Filter (CAN_HVLOW_ADDR, 0, 0), can__hvlow_receive},          //RXF2
  {standard2515Filter (CAN_BAT_TEMP_ADDR, 0, 0), can__hvtemp_receive}  //RXF3
} ;
#endif

void can__start()
{
  
  //--- Configure ACAN2515
  //Serial.println ("Configure ACAN2515") ;

  // No filter
  //const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;

  // With filter
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; },
                                        rxm0, rxm1, filters, 4) ;
  
  if (errorCode == 0) {
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Propagation Segment: ") ;
    Serial.println (settings.mPropagationSegment) ;
    Serial.print ("Phase segment 1: ") ;
    Serial.println (settings.mPhaseSegment1) ;
    Serial.print ("Phase segment 2: ") ;
    Serial.println (settings.mPhaseSegment2) ;
    Serial.print ("SJW: ") ;
    Serial.println (settings.mSJW) ;
    Serial.print ("Triple Sampling: ") ;
    Serial.println (settings.mTripleSampling ? "yes" : "no") ;
    Serial.print ("Actual bit rate: ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact bit rate ? ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point: ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
  } else {
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX) ;
  }
  
  //Non-zero indicates error
  if (errorCode) {
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX);
  }
 
}

void can__stop()
{
  can.end();
}

static uint32_t gBlinkLedDate = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static uint32_t gSentFrameCount = 0 ;

void can__send_test()
{
  CANMessage frame;
  frame.id = 0x7EE;
  frame.len = 8;
  frame.data[0] = 0x53; 
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 200 ;
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
      Serial.print ("Sent: ") ;
      Serial.println (gSentFrameCount) ;
    } else {
      Serial.println ("Send failure") ;
    }
  }
}

void can__receive()
{
  can.dispatchReceivedMessage();
  CANMessage frame ;

  /*
  if (can.available()) {
    can.receive(frame);
    Serial.print("ID: ");
    Serial.println(frame.id);
    Serial.print("Data: ");
    for (int i = 0; i < 8; i++) {
      Serial.println(frame.data[i]);
    }
  }
  */
  
  /*
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 200 ;
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
      Serial.print ("Sent: ") ;
      Serial.println (gSentFrameCount) ;
    } else {
      Serial.println ("Send failure") ;
    }
  }
  */
  if (can.available ()) {
    can.receive (frame) ;
    //Serial.println((frame.data[1]) | (frame.data[0] << 8));
  }
  
}
