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
 */


#include <RTClib.h>
RTC_DS3231 rtc;// declaring the RTC module

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

unsigned long lastTimeDisplay = 0;

struct customAlarm {
  short alarmID = -1;
  short outPin;
  bool alarmMode;   // 0 - short time trigger, 1 - persist trigger
  short switchDuration // length of time that the alarm will remain active before turning off
  DateTime rtcTime;
  bool hasTriggered;
  bool willRepeat;
};

short registeredAlarms = 0;

customAlarm alarmArray[200];
void ICACHE_RAM_ATTR lowPowerSleep(); //Add to cache the ISR (Only for ESP12e)

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

void setCurrentTime(){
  
  if(!stringComplete) return;
  Serial.println("Setting the current time");
  char _dateTime[39]; 
  // Time format "yyyy/MM/dd hh/mm/ss"
  short spcIndex = inputString.indexOf(' ');
  String dateTime = inputString.substring(spcIndex+1);

  // Change the magic numbers into for loop
  short yyyy = dateTime.substring(0, 4).toInt();
  short MM = dateTime.substring(5, 7).toInt();
  short dd = dateTime.substring(8, 10).toInt();
  short hh = dateTime.substring(11, 13).toInt();
  short mm = dateTime.substring(14, 16).toInt();
  short ss = dateTime.substring(17, 19).toInt();
  
  rtc.adjust(
    DateTime(yyyy, MM, dd, hh, mm, ss)
  );

  sprintf(
    _dateTime,
    "Extracted datetime: %02d/%02d/%02d %02d:%02d:%02d",
    yyyy, MM, dd, hh, mm, ss
  );
  Serial.println(_dateTime);
}

short scanAlarms(){
  // Scan all available alarms then check what to do on each
}

void processAlarm(){
  // Check whether activate or kill an alarm or turn off its effect
}

void calculateNextSleep(){
  // Scan all available alarms then check if sleep is posible to conserve energy
  // todo:
  // Check if there are active pins from alarm
}

void createNewAlarm(){
  // Receive specs for new alarm then check for collision
}

void getAllAlarms(){
  // Return the array of alarms in JSON format
}

void deleteAlarm(){
  // Remove the registered alarm
}
