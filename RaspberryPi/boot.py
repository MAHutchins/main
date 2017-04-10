#This script tweets a random number and prints some diagnostic information. Place in /etc/profiles to run on login
#!usr/bin/python
print("Boot script started")

import random
import datetime
from twython import Twython
print("Twython imported successfully.")
#auth.py is a copy of auth.py in /home/pi/twitter
from auth import (
        conKey,
        conSec,
        accTok,
        accSec
)
print("API info imported successfully.")

n = random.uniform(0,10)
t = datetime.datetime.now()
tweetStr = t.strftime('%m/%d/%Y %H:%M:%S ') + str(n)

print("Tweet is " + tweetStr)
print("Sending boot tweet...")
api=Twython(conKey,conSec,accTok,accSec)
api.update_status(status=tweetStr)
print("Boot tweet sent successfully")
