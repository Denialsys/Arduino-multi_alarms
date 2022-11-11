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
    'willRepeat': False
}


def process_alarm(alarmData):
    if alarmData['alarmID'] == -1:
        return

    currentDatetime = datetime.datetime.now().strftime("%H:%M:%S.%f")
    rtcTime = datetime.datetime.strptime(alarmData['rtcTime'], "%H:%M:%S.%f")
    timeDelta = currentDatetime - rtcTime

    if 0 < timeDelta.total_seconds() < timeThreshold:
        print("withinThreshold")
        if not alarmData['hasTriggered'] or alarmData['willRepeat']:
            if alarmData['alarmMode'] == 0:
                print(f'Switching Off: {alarmData["alarmID"]}')
            elif alarmData['alarmMode'] == 1:
                print(f'Switching On: {alarmData["alarmID"]}')
            else:
                print(f'Transient switching the: {alarmData["alarmID"]}')
        else:
            print('Pass 1')
            pass
    else:
        if timeDelta.total_seconds() >= alarmData['switchDuration']:
            if alarmData['alarmMode'] == 0:
                print(f'[Inverting] Switching On: {alarmData["alarmID"]}')
            elif alarmData['alarmMode'] == 1:
                print(f'[Inverting] Switching Off: {alarmData["alarmID"]}')
            else:
                print(f'[Inverting] Transient switching the: {alarmData["alarmID"]}')

        else:
            print('Pass 2')
            pass
