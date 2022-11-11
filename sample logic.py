'''
    Author: Jenver I.

    Sample core logic for scanning the alarm arrays.
    Compilation and upload to the microcontroller takes too much time
    this is used only for prototyping and testing

    Limitations: currently will not support high to low alarm signals
'''

import datetime
timeThreshold = .020     ## milliseconds
alarmList = [
    {   ## Passed
        'alarmID' : 0,  ## Will turn ON, turn Off after 1 seconds
        'outPin': 1,
        'alarmMode': 2, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 1, ## milliseconds multiply by 1000
        'rtcTime': '2:55:2.0',
        'hasTriggered': False,
        'willRepeat': False
    }, { ## Passed
        'alarmID' : 1,  ## Will turn ON, turn Off after 2 seconds
        'outPin': 1,
        'alarmMode': 2, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 2,
        'rtcTime': '2:55:2.0',
        'hasTriggered': False,
        'willRepeat': False
    }, { ## Passed
        'alarmID' : 2,  ## Will turn ON and never turn off
        'outPin': 1,
        'alarmMode': 1, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 1,
        'rtcTime': '2:55:2.0',
        'hasTriggered': False,
        'willRepeat': False
    }, { ## Passed
        'alarmID' : 3,  ## Will turn Off and never turn On
        'outPin': 1,
        'alarmMode': 0, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 4,
        'rtcTime': '2:55:2.0',
        'hasTriggered': False,
        'willRepeat': False
    }, { ## Passed
        'alarmID' : 4,  ## Will turn On once
        'outPin': 1,
        'alarmMode': 2, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 5,
        'rtcTime': '2:55:2.0',
        'hasTriggered': True,
        'willRepeat': False
    }, { ## Passed
        'alarmID' : 5,  ## Will turn On and repeat indefinitely
        'outPin': 1,
        'alarmMode': 2, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 5,
        'rtcTime': '2:55:2.0',
        'hasTriggered': True,
        'willRepeat': True
    }, { ## Passed
        'alarmID' : -1,  ## Will never be processed
        'outPin': 1,
        'alarmMode': 2, ##0 - Low,  1 - High, 2 - Transient
        'switchDuration': 1,
        'rtcTime': '2:55:2.0',
        'hasTriggered': False,
        'willRepeat': False
    }

]

def process_alarm(alarmData):
    if alarmData['alarmID'] == -1:
        print(f'Pass on empty alarm')
        return

    # currentDatetime = datetime.datetime.now().strftime("%H:%M:%S.%f")
    currentDatetime = datetime.datetime.strptime('2:55:7.00', "%H:%M:%S.%f")
    rtcTime = datetime.datetime.strptime(alarmData['rtcTime'], "%H:%M:%S.%f")
    timeDelta = currentDatetime - rtcTime

    print(f'total seconds {timeDelta.total_seconds()}')
    if 0 <= timeDelta.total_seconds() <= timeThreshold:
        if alarmData['hasTriggered'] and not alarmData['willRepeat']:
            print('Pass 0')
            pass

        if not alarmData['hasTriggered'] or alarmData['willRepeat']:
            if alarmData['alarmMode'] == 0:
                print(f'Switching Off: {alarmData["alarmID"]}')
            elif alarmData['alarmMode'] == 1:
                print(f'Switching On: {alarmData["alarmID"]}')
            else:
                print(f'Transient switching the: {alarmData["alarmID"]}')

            alarmData["hasTriggered"] = True
        else:
            print('Pass 1')
            pass
    else:
        if timeDelta.total_seconds() >= alarmData['switchDuration']:
            if alarmData['alarmMode'] == 0:
                print(f'[Inverting] Ignoring alarm mode 0')
            elif alarmData['alarmMode'] == 1:
                print(f'[Inverting] Ignoring alarm mode 1')
            # if alarmData['alarmMode'] == 2:
            else:
                print(f'[Inverting] Transient switching the: {alarmData["alarmID"]}')
        else:
            print('Pass 2')
            pass

    print(f'Alarm data: \n{alarmData}\n')


# process_alarm(alarmData)

for i in alarmList:
    process_alarm(i)