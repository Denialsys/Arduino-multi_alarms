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

void processAlarm(customAlarm &alarmData){
  // Check whether activate or kill an alarm or turn off its effect

  // Alarm is not deleted or invalid
  if (alarmData.alarmID == -1) return;

  Datetime currentDatetime = rtc.now();
  TimeSpan timeDelta = ccurrentDatetime - alarmData.rtcTime;
  bool HourMinuteMatched = isHourMinutesEqual(timeDelta.hours(), timeDelta.minutes());

  Serial.print("Total hours diff ");
  Serial.print(timeDelta.hours(), DEC);
  Serial.print(" total minutes diff ");
  Serial.print(timeDelta.minutes(), DEC);
  Serial.print(" total seconds diff ");
  Serial.print(timeDelta.seconds(), DEC);

  if (HourMinuteMatched && 0 <= int(timeDelta.seconds()) <= timeThreshold){
    if (alarmData.hasTriggered && !alarmData.willRepeat){
      Serial.println("Pass 0");
      return;
    }

    if (!alarmData.hasTriggered || alarmData.willRepeat){
      Serial.print("Switching ")
      if (alarmData.alarmMode == 0){  // Stay LOW
        digitalWrite(alarmData.outPin, LOW);
        Serial.print("Off");

      } else if (alarmData.alarmMode == 1){  // Stay HIGH
        digitalWrite(alarmData.outPin, HIGH);
        Serial.print("On");

      } else {  // Will be switched off later
        digitalWrite(alarmData.outPin, HIGH);
        Serial.print("Transient");
      }

      alarmData.hasTriggered = true;
      Serial.print(" the alarm: ");
      Serial.println(alarmData.alarmID);
    } else {
      // Pass
    }

  } else {
    if (HourMinuteMatched && int(timeDelta.seconds()) >= alarmData.switchDuration){
      if (alarmData.alarmMode == 2){
        digitalWrite(alarmData.outPin, LOW);
        Serial.println("[Inverting] Transient switch");
      }
    } else {
      // Pass
    }
  }
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

bool isHourMinutesEqual(byte hr, byte min){
  if (int(hr) == 0 && int(min) == 0) return true;
  else: return false;
}
