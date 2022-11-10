'''
    Author: Jenver I.

    Sample core logic for scanning the alarm arrays.
    Compilation and upload to the microcontroller takes too much time
    this is used only for prototyping and testing
'''

import datetime
timeThreshold = 100     ## milliseconds
alarmList = []
alarmData = {
    'alarmID' : -1,
    'outPin': 1,
    'alarmMode': 1, ##0 - Low,  1 - High, 2 - Transient
    'switchDuration': 100,
    'rtcTime': '2:55:2.0',
    'hasTriggered': False,
    'willrepeat': False
}


def process_alarm(alarmData):
    if alarmData['alarmID'] == -1:
        return
    currentDatetime = datetime.datetime.now().strftime("%H:%M:%S.%f")
    rtcTime = datetime.datetime.strptime(alarmData['rtcTime'], "%H:%M:%S.%f")
    timeDelta = currentDatetime - rtcTime
    if 0 < timeDelta.total_seconds() < timeThreshold:
        print("withinThreshold")
    
