'''
Created on 21/02/2013

@author: grant

This program will hopefully
 * Determine if user is active (screen saver)
 * Announce to the user every so often what time they have left
'''

import getpass
import os
import time
import logging

from subprocess import call

# get the user name that is logged in currently
userName = getpass.getuser()

logger = logging.getLogger('timeWatcher')
hdlr = logging.FileHandler(os.path.expanduser('~') + '/.timeWatcher')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
logger.addHandler(hdlr) 
logger.setLevel(logging.INFO)


def sendCommonMessage(message):
    call(['notify-send',message,'-i','/usr/share/icons/gnome/24x24/status/dialog-warning.png','-a','TimeWatcher'])    


logger.info('TimeWatcher Started')

# default notification time is 15 mins
sleepTime = 15

noUserTimeLimit = 0

while 1:
    # get the user name that is logged in currently
    userName = getpass.getuser()
    
    timeLeftfileLocation = "/var/lib/timeWatcher/" + userName
    
    # open the text file
    try:
        timeLeftFile = open(timeLeftfileLocation, "r")
    except IOError:
        #can't open file - stop application
        logger.info('TimeWatcher Stopped - no user file found')
    finally:
        # get the time left from the file
        timeLeft = timeLeftFile.readline()
        timeLeftFile.close()

        
    loginTimeFileLocation = "/etc/security/time.conf"
    
    try:
        loginTimeFile = file(loginTimeFileLocation, "r")
                        
        today = time.strftime("%a")
        
        today = today[:-1]
        
        # Search for the time restriction line for this user
        for userLine in loginTimeFile:
                if userName in userLine:            
                    start = userLine.find(today)
                    end = userLine.find(' ', start)
                    pamLoginTime = userLine[start:end]
                    pamLoginTime = pamLoginTime[7:]
                    currentTime = time.strftime("%H%M")
                    if int(currentTime) + int(timeLeft) > int(pamLoginTime):
                        timeLeft = int(pamLoginTime) - int(currentTime)
                        
                    noUserTimeLimit = 1
                else:
                    noUserTimeLimit = 0
    except IOError:
        #can't open the pam security File
        logger.error('TimeWatcher Error - cannot open time.conf')

    loginEndTime = 0
    # if less than 4 mins left
    if int(timeLeft) <= 4:
        logger.info('User ' + userName + ' has been warned. Less than 4 left')
        message = userName.title() + \
                 ' You need to start saving your work!\r' + \
                 'The system will log you out in less than ' + str(timeLeft) + ' mins'
        sendCommonMessage(message)
        # Annoying pop-up every minute!
        sleepTime = 1
    # between 4 and 10 mins left
    elif 4 < int(timeLeft) < 10:
        logger.info('User ' + userName + ' has been warned. Between 4 and 10 mins left')
        message = 'Hi ' + userName.title() + \
                  ' \r' + 'You have ' + str(timeLeft) + 'mins left for today' + \
                  '\rYou will automatically logged out in ' + str(timeLeft) + ' mins'
                  
        sendCommonMessage(message)
        # annoying pop-up every 2 mins
        sleepTime = 2
        
    # more than 10 mins left
    elif int(timeLeft) >= 10:
        logger.info('User ' + userName + ' has been warned. More than 10 mins left')
        if noUserTimeLimit == 0:
            message = 'Hi ' + userName.title() + \
                  ' \r' + 'You have no time restrictions today' + \
                  '\rThe system will log you out in ' + timeLeft + ' mins'
        elif noUserTimeLimit == 1:
            message = 'Hi ' + userName.title() + \
                  ' \r' + 'You have ' + timeLeft + ' left mins for today' + \
                  '\rThe system will log you out at ' + pamLoginTime[:2] + ':' + pamLoginTime[2:]
        sendCommonMessage(message)

        # annoying pop-up every 15 or less mins
        if int(sleepTime) >= int(timeLeft):
            sleepTime = int(timeLeft)
            
    logger.info('Sleeping for ' + str(sleepTime*60) + ' seconds')

    # Go to sleep for a little while
    time.sleep(sleepTime*60)
    
    
logger.info('TimeWatcher Stopped')
