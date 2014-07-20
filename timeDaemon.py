'''
Created on 27/02/2013
 
@author: grant

This script 
    * replenishes time each day
    * Figures out who is logged in
    * decrements their time file
    * maybe logs them out
'''

import os
import subprocess
import time
import datetime
import logging

from datetime import datetime, date

# important paths or variables
masterTimeFilePath = '/etc/timeWatcher/'
userTimeFilePath = '/var/lib/timeWatcher/'
loginTimeFileLocation = "/etc/security/time.conf"

logger = logging.getLogger('timeDaemon')
hdlr = logging.FileHandler('/var/log/timeDaemon.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
logger.addHandler(hdlr) 
logger.setLevel(logging.INFO)


def modification_date(filename):
    t = os.path.getmtime(filename)
    #return datetime.datetime.fromtimestamp(t)
    return time.strftime("%d %m %Y", time.localtime(t))

def checkPamFile(userName):
    try:
        loginTimeFile = file(loginTimeFileLocation, "r")
    except IOError:
        #can't open the pam security File
        logger.error('Time Daemon cannot open time.conf')
    finally:
        logger.info('Checking PAM Permissions')
        today = time.strftime("%a")
        today = today[:-1]
        # Search for the time restriction line for this user
        for userLine in loginTimeFile:
            if userName in userLine:
                start = userLine.find(today)
                end = userLine.find(' ', start)
                pamLoginTime = userLine[start:end]
                pamLoginTimeStart = pamLoginTime[2:6]
                pamLoginTimeEnd = pamLoginTime[7:]
                currentTime = time.strftime("%H%M")
                if int(currentTime) < int(pamLoginTimeStart):
                    subprocess.call(['pkill', '-KILL', '-u', userName])
                    subprocess.call(['passwd', '-l', username])
                    logger.info('BANG! User ' + userName + ' is dead - Logging in too early for pam')
                if int(currentTime) > int(pamLoginTimeEnd):
                    logger.info('BANG! User ' + userName + ' is dead - logged in past pam end time')
                    subprocess.call(['pkill', '-KILL', '-u', userName])
                    subprocess.call(['passwd', '-l', username])
                    
def checkTimeOutFile(userName):
    try:
        timeLeftFile = open(userTimeFilePath+userName, "r+")
    except IOError:
        #can't open file - stop application
        logger.error('TimeWatcher did not find a file for ' + userName)
    finally:
        # get the time left from the file
        timeLeft = timeLeftFile.readline()
        timeLeft = timeLeft.rstrip()
        #Check to see if it has "none" in it
        if timeLeft != 'none':
            # Take 1 minute away from the file
            timeLeft = int(timeLeft) - 1
            # if the user still has time left                
            if timeLeft > 0:
                logger.info('Changing ' + userName + ' time to ' + str(timeLeft))
                # Rewind the file pointer
                timeLeftFile.seek(0, 0)
                # write time back into file
                timeLeftFile.write(str(timeLeft))
                timeLeftFile.close()
            else:
                subprocess.call(['pkill', '-KILL', '-u', userName])
                subprocess.call(['passwd', '-l', username])
                logger.info('BANG! User ' + userName + ' is dead - no more time left!')
        else:
            logger.info(userName + ' does not have any time restrictions at the moment')
    return timeLeft

    
while 1:    
    # get todays date in this format.
    logger.info('Todays date is ' + time.strftime("%d-%m-%Y"))
    currentTime = time.strftime("%d %m %Y")
    
    logger.info('Checking Time stamps on user files')
    
    # get the files in the directory
    dirEntries = os.listdir(userTimeFilePath)
    
    previousEntry = "1Bob"
    
    # for each file
    for entry in dirEntries:
        # compare the previous entry with the current entry so we don't do the same user twice
        # if the previous entry is the same as the current entry don't process it
        
        if entry == previousEntry:
            logger.info('Processed this user already')
        else:
            userTimeFileDate = modification_date(userTimeFilePath+entry)
            
            if currentTime != userTimeFileDate:
                logger.info(entry+' timestamp does not match - adding more time')
                masterTimeFile = open(masterTimeFilePath + entry + '.time')
                userTimeFile = open(userTimeFilePath + entry, "r+")
                userTimeFile.truncate()
                line = masterTimeFile.readline()
                timeLeft = line.split()

                if len(timeLeft) > 3:
                    # Format is Su, xx, Mo, xx, Tu, xx, We, xx, Th, xx, Fr, xx, Sa, xx
                    day = date.isoweekday(datetime.today())
                    if day == 7:
                        day = 0
                    
                    day = day * 2
                    
                    userTimeFile.write(str(timeLeft[day+1]))
                    
                    print 'Writing ', timeLeft[day+1], ' to file'
#                    print timeLeft[2]

                else:
                    # Format is Sa, Su, xx
                    try:
                        userTimeFile.write(str(timeLeft[2]))
                    except:
                        print userTimeFile.errors
                userTimeFile.close()
            else:
                logger.info('user ' + entry + ' has time for today')    
        
        previousEntry = entry
        
            
    proc = subprocess.Popen(['users'], stdout=subprocess.PIPE)
    
    output = proc.stdout.read()
    
    output = output.split(" ")
    # god help us if there is actually someone called 1bob
    previousUser = "1bob"
    
    for userName in output:
        # if we have checked that username - skip to the next
        if previousUser.strip() == userName.strip():
            logger.info('User ' + userName.strip() + ' has been checked already')
        
        else:
            checkPamFile(userName)

            checkTimeOutFile(userName)
                    # user is out of time - kill session
                    #subprocess.call(['pkill', '-KILL', '-u', userName])
#                    print('BANG! User ' + userName + ' is dead')
        previousUser = userName
        
    logger.info('Sleeping for 60 seconds')
    # sleep for a minute
    time.sleep(60)

