/*
 * Author: Jenver I.
 * 
 * For DS3231 documentations 
 * Visit: https://adafruit.github.io/RTClib/html/_r_t_clib_8h.html#abf9692bbba5b3b3adbb6939fe05c0cb3
 * 
 * Sketch for using the DS3231 with the ESP12e
 * Can be used for home automation, or for multiple trigger of a device
 * Primarily will be used for custom timelapse trigger
 * 
 * This will have the functions to:
 *    - set the current time
 *    - set multiple alarms
 *    - delete alarms
 *    - get the alarm status
 *    - activate the boost and switch then deactivate boost again
 *    - deactivate boost and switch
 *    
 * 
 * Limitations:
 *    - currently will not support high to low alarm signals
 *    - pulse length for transient alarms only supports less than 1 minute
 */


#include <RTClib.h>
RTC_DS3231 rtc;// declaring the RTC module


String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

struct customAlarm {
  short alarmID = -1;
  short outPin;
  short alarmMode;   // 0 - short time trigger, 1 - persist trigger
  short switchDuration; // length of time that the alarm will remain active before turning off
  DateTime rtcTime;
  bool hasTriggered;
  bool willRepeat;
};
short registeredAlarms = 0;
customAlarm alarmArray[200];
short timeThreshold = 1;  // 1 Second tolerance

#include "alarmFunctions.h" // Inherit all the global variables

void setup() {
  
  Serial.begin(9600);
  
  if(!rtc.begin()) {
      Serial.println("Couldn't find RTC!");
      Serial.flush();
      while (1) delay(10);
  }
  
  if(rtc.lostPower()) {
      Serial.println("Power was lost in RTC please set the date and time");
  }
  
  // we don't need the 32K Pin, so disable it
  rtc.disable32K();

  // We'll use the SQW pin for alarm so disable the pwm
  rtc.writeSqwPinMode(DS3231_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte add it to the inputString:
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    //Serial data has ended parse
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
